FROM gcc:13.2 AS builder

RUN set -ex; \
    apt-get update && apt-get install -y --no-install-recommends \
        cmake \
        tor \
        libzmq3-dev \
        net-tools \
        iputils-ping \
        dnsutils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build
COPY . /build

RUN cmake -D CPPZMQ_BUILD_TESTS:BOOL=OFF . && \
    make && make install

FROM debian:bookworm-slim

RUN set -ex; \
    apt-get update && apt-get install -y --no-install-recommends \
        tor \
        curl \
        libzmq5 \
        net-tools \
        iputils-ping \
        dnsutils \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder build/libtoralize.so /usr/local/lib/libtoralize.so
COPY install.sh /usr/local/bin/toralize
RUN chmod 755 /usr/local/bin/toralize

EXPOSE 9050

CMD ["tor"]
