FROM rust:1.67 as builder
WORKDIR /usr/src/myapp
COPY . .
RUN cargo install --path .

FROM debian:bullseye-slim
#RUN apt-get update && apt-get install -y extra-runtime-dependencies && rm -rf /var/lib/apt/lists/*
COPY --from=builder /usr/local/cargo/bin/hello /usr/local/bin/hello
CMD ["hello"]

#checkov:skip=CKV_DOCKER_2:No need for healthcheck as development container used to build and not run stuff
#checkov:skip=CKV_DOCKER_3:No need for user as development container used to build and not run stuff