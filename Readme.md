# [Terraform Cloud Workspace tfc](https://app.terraform.io/app/sdinc/workspaces/tfc)

## Dependancies

* docker: one way to install is with [docker desktop](https://www.docker.com/products/docker-desktop/) 
* task: one way to install is with a ```sh -c "$(curl --location https://taskfile.dev/install.sh)" -- -d -b ~/.local/bin``` more details at [reference](https://taskfile.dev/installation/#get-the-binary)

## CI

* each push to the repo should trigger a github actions
* I have also setup azure pipelines but you have to push to the azure hosted repo to trigger this 

## Help

```bash
brody@brody-Precision-5540:~/workspace/github/tfc$ task
Hello, Welcome to SDinc ( Specialty Diagnostics Incorporated )
task: Available tasks for this project:
* aws-cli:            aws sts get-caller-identity
* aws-who:            aws sts get-caller-identity
* az-login:           auth to azure cli
* az-shell:           run azure shell
* checkov:            run checkov via docker
* clean:              remove generated files
* rust-all:           run the SDLC(Software Development Life Cycle)
* rust-build:         build the rust container, rust application
* rust-format:        format my code
* rust-shell:         launch a rust shell/environment, ie rustc and cargo are on the path
* rust-test:          run the rust tests
* sd-down:            pull site from s3
* sd-up:              push site from local to s3
* sdinc-build:        build sdinc container with bash shell
* sdinc-shell:        run sdinc container as bash shell
* sfefoil-down:       pull site from s3
* sfefoil-up:         push site from local to s3
* tf-apply:           terraform apply via docker backend terraform cloud
* tf-init:            terraform init via docker backend terraform cloud
* tf-login:           terraform login via docker backend terraform cloud
* tf-plan:            terraform plan via docker backend terraform cloud
Tue Aug 13 02:46:05 AM UTC 2024
brody@brody-Precision-5540:~/workspace/github/tfc$ 

```