FROM docker.educg.net/cg/os-contest:20250226

RUN apt update
RUN apt install -y --no-install-recommends \
    bison flex libssl-dev bridge-utils dnsmasq sudo iptables

RUN rustup install nightly-2024-11-05
RUN rustup default nightly-2024-11-05
RUN rustup target add riscv64gc-unknown-none-elf --toolchain nightly-2024-11-05
RUN rustup target add riscv64gc-unknown-linux-musl --toolchain nightly-2024-11-05
RUN rustup target add x86_64-unknown-linux-musl --toolchain nightly-2024-11-05
RUN rustup component add rust-src --toolchain nightly-2024-11-05
RUN rustup component add clippy --toolchain nightly-2024-11-05
RUN rustup component add rustfmt --toolchain nightly-2024-11-05
RUN cargo +nightly-2024-11-05 install cargo-binutils

RUN cargo install --git https://github.com/DragonOS-Community/DADK.git --branch 007/docker-multiarch

ADD --checksum=sha256:b6b058ab77cf21c806db409d1fb2ad4b43fa23832616216099cf8168274f16b6 https://github.com/loongson/build-tools/releases/download/2025.02.21/x86_64-cross-tools-loongarch64-binutils_2.44-gcc_14.2.0-glibc_2.41.tar.xz /opt/x86_64-cross-tools-loongarch64-binutils_2.44-gcc_14.2.0-glibc_2.41.tar.xz
RUN tar -xvf /opt/x86_64-cross-tools-loongarch64-binutils_2.44-gcc_14.2.0-glibc_2.41.tar.xz -C /opt
RUN rm /opt/x86_64-cross-tools-loongarch64-binutils_2.44-gcc_14.2.0-glibc_2.41.tar.xz
ENV PATH=/opt/cross-tools/bin:$PATH

ENTRYPOINT ["tini", "--"]
