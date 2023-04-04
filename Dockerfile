FROM srzzumix/googletest:latest

MAINTAINER joramuns

COPY ./ /code/src/
RUN apt update && apt install -y qtbase5-dev qt5-qmake

WORKDIR /code/src/
ENTRYPOINT ["/bin/bash"]
