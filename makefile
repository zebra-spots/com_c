# Makefile

server:
        gcc main.c -o server

server1:

        gcc main1.c -o server1

all:
        gcc main.c -o server -save-temps

nuke:
        rm -f server*

clean:
        rm server

clean.o:
        rm server.o

clean.s:
        rm server.s

clean.i:
        rm server.i
