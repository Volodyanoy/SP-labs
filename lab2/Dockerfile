FROM ubuntu:latest

RUN apt-get update && apt-get install -y gcc gdb gcc-multilib

COPY ./c.c .
COPY ./s.s .

RUN gcc -g3 -m32 -no-pie ./s.s -o ./prog-s
RUN gcc -g3 ./c.c -o ./prog-c

