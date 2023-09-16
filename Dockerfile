FROM mcr.microsoft.com/azure-cli:2.51.0-arm64 AS az

FROM hashicorp/terraform:1.5.2 AS tf

#https://github.com/aws/aws-cli/blob/v2/docker/Dockerfile
FROM public.ecr.aws/aws-cli/aws-cli:2.13.18 AS aws

RUN yum install bash -y

#might change this later but for now leave it as in the original image
WORKDIR /aws
ENTRYPOINT ["/usr/local/bin/aws"]

#checkov:skip=CKV_DOCKER_2:No need for healthcheck as development container used to build and not run stuff
#checkov:skip=CKV_DOCKER_3:No need for user as development container used to build and not run stuff