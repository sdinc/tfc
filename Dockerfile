#FROM hashicorp/terraform:1.8.3 AS tf
FROM hashicorp/terraform:latest AS tf

#FROM mcr.microsoft.com/azure-cli:2.51.0-arm64 AS az
FROM mcr.microsoft.com/azure-cli:latest AS az
COPY --from=tf /bin/terraform /usr/local/bin/

# FROM gcr.io/google.com/cloudsdktool/google-cloud-cli:476.0.0
FROM gcr.io/google.com/cloudsdktool/google-cloud-cli:latest as google
COPY --from=tf /bin/terraform /usr/local/bin/

RUN apt-get update
RUN apt-get install bash

#https://github.com/aws/aws-cli/blob/v2/docker/Dockerfile
#FROM public.ecr.aws/aws-cli/aws-cli:2.13.18 AS aws
#
#RUN yum install bash python3-pip python3-devel -y
#RUn yum update -y
#
#RUN pip3 install azure-cli

#might change this later but for now leave it as in the original image
#WORKDIR /aws
#ENTRYPOINT ["/usr/local/bin/aws"]

#checkov:skip=CKV_DOCKER_2:No need for healthcheck as development container used to build and not run stuff
#checkov:skip=CKV_DOCKER_3:No need for user as development container used to build and not run stuff
#checkov:skip=CKV_DOCKER_7:We want to use the latest so skip this rule