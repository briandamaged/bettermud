# BetterMUD #

A minor update to Ron Penton's BetterMUD that runs on modern Linux operating systems.

## Installation ##

The easiest way to get the application up and running is via [docker-compose](https://docs.docker.com/compose/install/).  Just do the following:

```shell
# Navigate to the root directory of this project
cd path/to/BetterMUD

# Launch everything via docker-compose
docker-compose up
```

This will automatically:

1. Build a Docker image from the [Dockerfile](./Dockerfile)
2. Launch the application

Alternatively, you can still compile the application on Linux [the old-fashioned way](./BetterMUD/readme.txt)

## Usage ##

Once the application has been launched, you can connect via [Telnet](https://en.wikipedia.org/wiki/Telnet) on port 5110:

```shell
telnet localhost 5110
```
