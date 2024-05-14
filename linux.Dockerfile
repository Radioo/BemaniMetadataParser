FROM ubuntu:24.04

WORKDIR /app

RUN apt-get update
RUN apt-get install -y build-essential libgtk-3-dev cmake git