FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    locales \
    g++ \
    make \
    pkg-config \
    check \
    lcov \
    gcovr \
    python3 \
    valgrind \
    libgtest-dev

RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8  
ENV LC_ALL en_US.UTF-8

WORKDIR /usr/src/app

COPY ./ /usr/src/app/

RUN 

#CMD ["python3", "-m", "http.server", "8000", "--directory", "report"]
