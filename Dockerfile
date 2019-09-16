FROM ubuntu:18.04

RUN apt-get update && \
    apt-get install --no-install-recommends -y \
      build-essential \
      python-dev \
      pkg-config && \
    rm -rf /var/lib/apt/lists/* && \
    useradd -ms /bin/bash mud

COPY . /usr/src/app
RUN chown -R mud:mud /usr/src/app

USER mud
WORKDIR /usr/src/app/BetterMUD
RUN make clean libs bettermud link

EXPOSE 5110

CMD ./bettermud
