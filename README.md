# [Terraform Cloud Workspace tfc](https://app.terraform.io/app/sdinc/workspaces/tfc)

## Dependancies

* docker: one way to install is with [docker desktop](https://www.docker.com/products/docker-desktop/) 
* task: one way to install is with a ```sh -c "$(curl --location https://taskfile.dev/install.sh)" -- -d -b ~/.local/bin``` more details at [reference](https://taskfile.dev/installation/#get-the-binary)


## Help

```bash
brody@brodys-MacBook-Pro tfc % task
Hello, Welcome to SDinc ( Specialty Diagnostics Incorporated )
task: Available tasks for this project:
* aws-build:          build a aws container with bash shell
* aws-cli:            aws sts get-caller-identity
* aws-web-down:       pull site from s3
* aws-web-up:         push site from local to s3
* aws-who:            aws sts get-caller-identity
* checkov:            run checkov via docker
* tf-apply:           terraform apply via docker backend terraform cloud
* tf-init:            terraform init via docker backend terraform cloud
* tf-login:           terraform login via docker backend terraform cloud
* tf-plan:            terraform plan via docker backend terraform cloud
Sat Sep 16 02:44:27 UTC 2023
```