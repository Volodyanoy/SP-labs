FROM ubuntu:latest

RUN apt-get update && apt-get install -y gcc gdb gcc-multilib

COPY ./c.c .

RUN gcc -g3 ./c.c -o prog

