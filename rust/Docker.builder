FROM rust:1.67 as builder
WORKDIR /usr/src/myapp
COPY . .
RUN cargo install --path .

RUN apt-get update && apt-get install -y bash debianutils && rm -rf /var/lib/apt/lists/*

RUN rustup component add rustfmt clippy

CMD ["bash"]