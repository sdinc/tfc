
## Loading the needed functions from the rules_docker repository

load("@io_bazel_rules_docker//container:container.bzl", \
"container_image")
load("@io_bazel_rules_docker//container:container.bzl", \
"container_push")

# container_image packages a new docker image, new layers \
can be added to a base image using its parameters

container_image(
    name = "sdinc_app",
    base = "@python_base//image",
)

# container_push pushes a local image to a registry of your\
 choice (Docker Hub, Google Registry, Gitlab registry or Github packages)

container_push(
    name = "publish",
    format = "Docker",
    image = ":sdinc_app",
    registry = "616843412874.dkr.ecr.us-east-1.amazonaws.com",
    repository = "sdinc-py",
    tag = "0.0.1",
)