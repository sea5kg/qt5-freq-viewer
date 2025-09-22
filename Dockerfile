FROM ubuntu:jammy

WORKDIR /opt/src

RUN apt update && apt install -y \
  build-essential \
  cmake \
  qtbase5-dev \
  qtdeclarative5-dev \
  qtquickcontrols2-5-dev
