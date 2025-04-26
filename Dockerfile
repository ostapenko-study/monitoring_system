FROM ubuntu:22.04

RUN apt update && apt install -y \
    build-essential \
    make \
    qt5-qmake \
    qtbase5-dev \
    qtbase5-dev-tools \
    libqt5websockets5-dev \
    wget \
    fuse \
    patchelf \
    desktop-file-utils \
    libssl-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

# Сюди скопіюємо проект
COPY ./src /workspace/src

COPY linuxdeployqt /usr/local/bin/linuxdeployqt
RUN chmod +x /usr/local/bin/linuxdeployqt

WORKDIR /workspace/src