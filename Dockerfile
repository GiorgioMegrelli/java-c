FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y openjdk-8-jdk
RUN rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app
