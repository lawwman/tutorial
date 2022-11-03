https://terragrunt.gruntwork.io/docs/getting-started/quick-start/

*Terragrunt is a thin wrapper that provides extra tools for keeping your configurations DRY, working with multiple Terraform modules, and managing remote state. Terragrunt will forward almost all commands, arguments, and options directly to Terraform, but based on the settings in your `terragrunt.hcl` file.*

- in `.tf`, the `terraform` block is used to set the `required_version`, `required_provider`, `backend` and so on.
- in `.hcl`, the `terraform` block is used to set the `source`, which is: the `.tf` files/modules that will be used.

# key features:

## keep backend configuration DRY

```
# a typical backend config in a tf file.
terraform {
  backend "s3" {
    bucket         = "my-terraform-state"
    key            = "stage/frontend-app/terraform.tfstate"
    region         = "us-east-1"
    encrypt        = true
    dynamodb_table = "my-lock-table"
  }
}
```
take note that aside from the `key` value of "stage/frontend-app/terraform.tfstate", the other values are the same. In `.tf`, a big problem for the `terraform` block is that you cannot reference variables.

the above example works for `stage/frontend-app` module as seen from the `key` value. but once you start adding more modules, you have to copy paste the same `terraform` block, and then carefully change the key value. SHIT! It does not support having a single source of truth.

Terragrunt allows you to keep your backend configuration DRY by defining it once in a root location and inheriting that configuration in all child modules. How to do it?
```
# <some path at least 1 lvl up from your child modules ok?>/terragrunt.hcl
remote_state {
  backend = "s3"
  generate = {
    path      = "backend.tf"
    if_exists = "overwrite_terragrunt"
  }
  config = {
    bucket = "my-terraform-state"

    key = "${path_relative_to_include()}/terraform.tfstate"
    region         = "us-east-1"
    encrypt        = true
    dynamodb_table = "my-lock-table"
  }
}
```

```
# child_path_for_maybe_aws_dynamodb/terragrunt.hcl
include "root" {
  path = find_in_parent_folders()
}
```
The find_in_parent_folders() helper will automatically search up the directory tree to find the root terragrunt.hcl and inherit the remote_state configuration from it.

## Keep provider configuration DRY

not very relevant. im lazy. https://terragrunt.gruntwork.io/docs/getting-started/quick-start/#keep-your-provider-configuration-dry. read it urself.

## Keep Terraform CLI arguments DRY
https://terragrunt.gruntwork.io/docs/getting-started/quick-start/#keep-your-terraform-cli-arguments-dry. read it urself punk.

