
FROM debian:buster

RUN apt-get update && apt-get install -y gcc

WORKDIR /app

COPY mertsumd.c .

RUN gcc -o mertsumd mertsumd.c

CMD ["./mertsumd"]
