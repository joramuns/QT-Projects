FROM srzzumix/googletest:latest

MAINTAINER joramuns

COPY ./src/ /code/src/
RUN apt update && apt install -y valgrind pkg-config

WORKDIR /code/src/
ENTRYPOINT ["make", "vg"]
