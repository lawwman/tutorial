https://registry.terraform.io/providers/hashicorp/aws/latest/docs

# Things to note
- Terraform loads all files in current directory ending with `.tf`
- Order does not matter in Terraform


# Blocks needed

## Terraform Block
Define Terraform settings such as
- `required_version` (Version of Terraform CLI required)
- `required_providers` (All the providers needed by the current module)

Each Terraform module must declare which providers it requires, so that Terraform can install and use them. Provider requirements are declared in a `required_providers` block.


### What are Providers?
Refer to: https://www.terraform.io/docs/language/providers/index.html
Essentially act as Plugins for terraform to install. They provide a set of resource types and/or data sources that Terraform can manage. *Every resource type is implemented by a provider; without providers, Terraform can't manage any kind of infrastructure.*

They are installed when you run `terraform init`.

### Example
```
terraform {
  required_version = ">= 0.14.0"  # version of terraform cli required
  required_providers {
    aws = {
      source  = "hashicorp/aws"  # where to install the provider from
      version = "~> 3.27"  # what version of the provider is required
    }
  }
}
```

## Provider Block
https://www.terraform.io/docs/language/providers/index.html

Each provider has two identifiers:
- A unique source address, which is only used when requiring a provider (e.g. `hashicorp/aws`).
- A local name, which is used everywhere else in a Terraform module (e.g. `aws`).

### Example
```
provider "aws" {  # using local name
  profile = "default"
  region  = "us-west-2"
}
```

The block allows you to provide more in depth configurations to the provider.


## Resource Block




var -> accessing variables


E.g. of a `main.tf`
```
terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 3.27"
    }
  }
}

provider "aws" {
  profile = "default"
  region  = "us-west-2"
}

resource "aws_instance" "example" {
  ami           = "ami-08d70e59c07c61a3a"  # argument
  instance_type = "t2.micro"

  tags = {
    Name = "ExampleInstance"
  }
}

output "instance_id" {
  description = "ID of the EC2 instance"
  value       = aws_instance.example.id
}

output "instance_public_ip" {
  description = "Public IP address of the EC2 instance"
  value       = aws_instance.example.public_ip
}
```

Commands: \
`terraform init` \
`terraform plan` \
`terraform apply` \
`terraform destroy` \
`terraform output`  used to query values defined in output blocks, after terraform apply \
`terraform console` used to inspect variables. Leave with `exit`

file types: \
`.tf`, `.tfvars` (does it have to be `terraform.tfvars`)


## `variables.tf` vs `terraform.tfvars`

`variables.tf` :
```
variable "region" {
    default = "us-east-1"
}
```
you can then reference from other `.tf` files with `var.region`.

`terraform.tfvars` :  (to persist variable values?) can be used to populate `variable` blocks. useful if default value not there
```
region="us-east-1"
```

### Resource block
E.g.
`resource "random_pet" "name" {}`. Syntax: `resource "<resource_type>" "<name>"`. Type and name are combined into a resource identifier in the format `resource_type.resource_name`. E.g. `random_pet.name` \

`<resource_type>` begins with `provider name` followed by underscore. In this case, `random` is the provider.

Resources have: \
- Arguments - can be `required` or `optional`. Configure the resource
- Attributes - values exposed by resource. 
- Meta-arguments - change resource_type behavior. e.g. `count`, `for_each`


## Variable block
3 optional arguments: `description`, `type`, `default`, `validation`, `sensitive`.

#### Variable types
(string, number, bool) - simple variable
(list, map, set) - collection variable

e.g. ["first string", "second string"] - list(string)

#### string interpolation
${} within "" can be used to insert variable values into string.

#### variable validation
Validation argument into Variable block. e.g.
```
validation {
    condition     = length(var.resource_tags["project"]) <= 16 && length(regexall("/[^a-zA-Z0-9-]/", var.resource_tags["project"])) == 0
    error_message = "The project tag must be no more than 16 characters, and only contain letters, numbers, and hyphens."
    }
```

## Locals
- You cannot reference a variable to define a variable. Thats where Locals come into play.
- Think of it as a variable that can be assigned with a variable.
- Users cannot override this value too.
```
locals {
  name_suffix = "${var.resource_tags["project"]}-${var.resource_tags["environment"]}"
}
```
reference with `local.name_suffix`.


## Modules
a directory with 1 or more `.tf` files is a module. Where you run the terraform command from, is the root module.

Can reference either local (build your own) or remote modules (lookup terraform registry).

```
module "module name" {
    source = "terraform-aws-modules/ec2-instance/aws"  # remote source path
}
```

When using new (remote | local) module for first time, run `terraform init` or `terraform get` to install. They are installed in `.terraform/modules` directory.

Module blocks do not need a `provider` block. They will inherit it from parent.


## Local files Terraform creates for you
- `terraform.tfstate` and `terraform.tfstate.backup`: These files contain your Terraform state, and are how Terraform keeps track of the relationship between your configuration and the infrastructure provisioned by it.

- `.terraform`: This directory contains the modules and plugins used to provision your infrastructure. These files are specific to a specific instance of Terraform when provisioning infrastructure, not the configuration of the infrastructure defined in .tf files.

- `*.tfvars`: Since module input variables are set via arguments to the module block in your configuration, you don't need to distribute any *.tfvars files with your module, unless you are also using it as a standalone Terraform configuration.


## Data sources
https://learn.hashicorp.com/tutorials/terraform/data-sources?in=terraform/configuration-language

Data blocks lets you load data from remote sources. E.g.
```
data "aws_availability_zones" "available" {
  state = "available"
}
```
https://registry.terraform.io/providers/hashicorp/aws/latest/docs/data-sources/availability_zones

Maybe can think of it as a variable block that you request for from some remote data source.


## Resource Dependency
implicit vs explicit dependency. 

### Implicit
Based on resource attributes, terraform can infer by itself dependencies.
```
resource "aws_instance" "example_a" {
  ami           = data.aws_ami.amazon_linux.id
  instance_type = "t2.micro"
}

resource "aws_eip" "ip" {  # elastic ip that depends on example_a instance being created first
    vpc = true
    instance = aws_instance.example_a.id
}
```
`instance = aws_instance.example_a.id` from this line refering to "example_a", knows to create `example_a` first and creates the infrastructure in the correct order.

### Explicit
For dependencies that are not so visible, we can use the `depends_on` argument.

For e.g. the EC2 instance requires a specific S3 bucket, but this is only visible in code. We then use `depends_on` to deploy it safely in order.


## Count
```
variable "instances_per_subnet" {
  description = "Number of EC2 instances in each private subnet"
  type        = number
  default     = 2
}

resource "aws_instance" "app" {
    count = var.instances_per_subnet * length(module.vpc.private_subnets)

    ami           = data.aws_ami.amazon_linux.id
    instance_type = var.instance_type

    subnet_id              = module.vpc.private_subnets[0]
    subnet_id              = module.vpc.private_subnets[count.index % length(module.vpc.private_subnets)]
    vpc_security_group_ids = [module.app_security_group.this_security_group_id]

# ...truncated...
}
```
Instances with the `count` attribute are a collection.
Each instance provisioned by the resource block with `count` will have a different incrementing value for `count.index`, starting with 0.

The name of resources or modules provisioned with count refers to the entire collection. In this example, `aws_instance.app` now refers to all of the EC2 instances. You can reference individual items in collections with the same notation as list indexing. For example, aws_instance.app[0].

You can create a list of all of the values of a given attribute for the items in the collection with a star. For instance, `aws_instance.app.*.id`.

## for_each
an argument you can define on a resource. You can define a map variable to input as an argument. Terraform will create same number of resources as keys in that map.
```
variable "project" {
  description = "Map of project names to configuration."
  type        = map
  default     = {
    client-webapp = {
      public_subnets_per_vpc  = 2,
      private_subnets_per_vpc = 2,
      instances_per_subnet    = 2,
      instance_type           = "t2.micro",
      environment             = "dev"
    },
    internal-webapp = {
      public_subnets_per_vpc  = 1,
      private_subnets_per_vpc = 1,
      instances_per_subnet    = 2,
      instance_type           = "t2.nano",
      environment             = "test"
    }
  }
}

module "vpc" {
    source  = "terraform-aws-modules/vpc/aws"
    version = "2.66.0"

    for_each = var.project
    name        = "web-server-sg-${each.key}-${each.value.environment}"
    # ...truncated...
}
```
Terraform will provision multiple VPCs, assigning each key/value pair in the `var.project` map to `each.key` and `each.value` respectively. With a list or set, each.key will be the index of the item in the collection, and `each.value` will be the value of the item.

Note that you cannot use both `count` and `for_each` in the same block.