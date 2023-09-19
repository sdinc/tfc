load("@io_bazel_rules_docker//container:container.bzl", "container_image")

container_image(
    name = "basic_alpine",
    base = "@alpine_linux_arm64//image",
    cmd = ["Hello World!"],
    entrypoint = ["echo"],
)