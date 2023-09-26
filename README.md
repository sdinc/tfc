# [Terraform Cloud Workspace tfc](https://app.terraform.io/app/sdinc/workspaces/tfc)

## Dependancies

* docker: one way to install is with [docker desktop](https://www.docker.com/products/docker-desktop/) 
* task: one way to install is with a ```sh -c "$(curl --location https://taskfile.dev/install.sh)" -- -d -b ~/.local/bin``` more details at [reference](https://taskfile.dev/installation/#get-the-binary)
* bazel: running as a container had problems with arm64 architexture on a MBP so I installed with brew ```brew install bazel``` [reference](https://bazel.build/install/os-x#install-on-mac-os-x-homebrew)   [general install](https://bazel.build/install)

## Help

```bash
brody@brodys-MacBook-Pro tfc % task
Hello, Welcome to SDinc ( Specialty Diagnostics Incorporated )
task: Available tasks for this project:
* aws-auth-ecr:          authenticate to aws ecr repo's
* aws-build:             build a aws container with bash shell
* aws-cli:               aws sts get-caller-identity
* aws-who:               aws sts get-caller-identity
* bazel-alpine:          bazel run :basic_alpine from workspace3 directory
* bazel-sdinc_aws:       bazel run :sdinc_aws from workspace1 directory
* checkov:               run checkov via docker
* checkov-deps:          run checkov via docker
* clean:                 clean all generated files
* mac-bb:                MBP bazel build from container
* sd-down:               pull site from s3
* sd-up:                 push site from local to s3
* sfefoil-down:          pull site from s3
* sfefoil-up:            push site from local to s3
* tf-apply:              terraform apply via docker backend terraform cloud
* tf-init:               terraform init via docker backend terraform cloud
* tf-login:              terraform login via docker backend terraform cloud
* tf-plan:               terraform plan via docker backend terraform cloud
Tue Sep 26 14:49:03 UTC 2023
brody@brodys-MacBook-Pro tfc %  
```