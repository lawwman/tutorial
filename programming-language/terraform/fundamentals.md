# [Files and Directories](https://www.terraform.io/language/files)
- Terraform loads all files in current directory ending with `.tf`
- Order does not matter in Terraform

*Terraform evaluates all of the configuration files in a module, effectively treating the entire module as a single document. Separating various blocks into different files is purely for the convenience of readers and maintainers, and has no effect on the module's behavior.*

# Terraform Block
Define Terraform settings such as
- `required_version` (Version of Terraform CLI required)
- `required_providers` (All the providers needed by the current module)

Each Terraform module must declare which providers it requires, so that Terraform can install and use them.

## What are Providers?
- https://www.terraform.io/docs/language/providers/index.html
- AWS provider: https://registry.terraform.io/providers/hashicorp/aws/latest/docs

Providers essentially act as Plugins for terraform to install. They provide a set of `resource` types and/or `data` sources that Terraform can manage. They are installed when you run `terraform init`.

> *Every resource type is implemented by a provider; without providers, Terraform can't manage any kind of infrastructure.*

Information for providers can be found within `.tf` scripts under:
- Terraform block, under: `required_providers`
- Provider block

Each provider has two identifiers:
- A unique source address, which is only used when requiring a provider (e.g. `hashicorp/aws`).
- A local name, which is used everywhere else in a Terraform module (e.g. `aws`).

## Example of providers in Terraform Block
```
terraform {
  required_version = ">= 0.14.0"  # version of terraform cli required
  required_providers {
    aws = {
      source  = "hashicorp/aws"  # provider source
      version = "~> 3.27"  # min version of provider
    }
  }
}

# Configure the AWS Provider
provider "aws" {
  profile = "default"
  region = "us-east-1"
}
```

# Storing State and Locks in a shared cloud with Terraform bloc
```
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

# [Resource Block](https://www.terraform.io/language/resources)
## Syntax
```
resource "aws_instance" "web" {
  ami           = "ami-a1b2c3d4"
  instance_type = "t2.micro"
}

syntax:
resource "<provider>_<resource type>" "<local_name>" {
  <argument1> = "some value"
  <argument2> = "some other value"
}
```
Resources have:
- Arguments - can be `required` or `optional`. Configure the resource
- Meta-arguments - change resource_type behavior. e.g. `count`, `for_each`
- Attributes - values exposed by resource.

## [`variables.tf` vs `terraform.tfvars`](https://stackoverflow.com/questions/56086286/terraform-tfvars-vs-variables-tf-difference)
*The distinction between these is of declaration vs. assignment.*

variable blocks (which can actually appear in any .tf file, but are in variables.tf by convention) declare that a variable exists:
```
# in variables.tf

variable "region" {
    default = "us-east-1"
}
```
This tells Terraform that this module accepts an input variable called `region`. you can then reference from other `.tf` files with `var.region`.

creating a `terraform.tfvars` is one of the few ways to populate `variable` blocks. useful if default value not there.
```
# in terraform.tfvars

region="us-east-1"
```

## Locals
You cannot assign a variable by referencing another variable. Thats where `Locals` come into play.
```
locals {
  name_suffix = "${var.resource_tags["project"]}-${var.resource_tags["environment"]}"
}
```
in other parts of you code, you can reference with `local.name_suffix`.

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


# Resource Dependency
implicit vs explicit dependency. 

## Implicit
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

## Explicit
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
    name     = "web-server-sg-${each.key}-${each.value.environment}"
    # ...truncated...
}
```
Terraform will provision multiple VPCs, assigning each key/value pair in the `var.project` map to `each.key` and `each.value` respectively. With a list or set, each.key will be the index of the item in the collection, and `each.value` will be the value of the item.

Note that you cannot use both `count` and `for_each` in the same block.