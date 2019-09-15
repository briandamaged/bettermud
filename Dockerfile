FROM ubuntu:18.04

RUN apt-get update && \
    apt-get install --no-install-recommends -y \
      build-essential \
      python-dev \
      pkg-config

COPY . /usr/src/app

WORKDIR /usr/src/app

