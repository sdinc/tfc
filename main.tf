terraform {
  cloud {
    organization = "sdinc"

    workspaces {
      name = "tfc"
    }
  }
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
    azurerm = {
      source  = "hashicorp/azurerm"
      version = "~> 3.0"
    }
    google = {
      version = "~> 4.0"
    }
  }
}

provider "azurerm" {
  skip_provider_registration = true # This is only required when the User, Service Principal, or Identity running Terraform lacks the permissions to register Azure Resource Providers.
  features {}
}

provider "google" {
  project     = "my-project-id"
  region      = "us-central1"
}

#For cloudfront, the acm has to be created in us-east-1 or it will not work
provider "aws" {
  region = "us-east-1"
}
