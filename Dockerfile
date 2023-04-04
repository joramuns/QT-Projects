FROM srzzumix/googletest:latest

MAINTAINER joramuns

COPY ./ /code/src/
RUN apt update && apt install -y snap

WORKDIR /code/src/
ENTRYPOINT ["/bin/bash"]
