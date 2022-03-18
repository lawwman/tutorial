# [Terragrunt](https://terragrunt.gruntwork.io/)
*Terragrunt is a thin wrapper that provides extra tools for keeping your configurations DRY, working with multiple Terraform modules, and managing remote state. Terragrunt will forward almost all commands, arguments, and options directly to Terraform, but based on the settings in your terragrunt.hcl file.*

## Good read on Why Terragrunt?
Terragrunt makes terraform more modular, allowing us to reuse terraform modules. `terragrunt.hcl` is used to coordinate your different terraform modules. Read the link below to find out more.
- https://terragrunt.gruntwork.io/docs/getting-started/quick-start/#key-features

TLDR: Don't repeat yourself.

*To use Terragrunt, add a single terragrunt.hcl file to the root of your repo, in the stage folder, and one terragrunt.hcl file in each module folder*