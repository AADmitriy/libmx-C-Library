FROM ubuntu:22.04

RUN apt-get update && apt-get install -y clang && apt-get install -y make

WORKDIR /libmx

COPY . .

CMD ["bash"]