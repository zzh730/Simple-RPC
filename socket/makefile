CC=gcc

all: server client

server: server_marshal.o marshal.o utils.o
	gcc server_marshal.o marshal.o utils.o -o server

client: client_marshal.o marshal.o utils.o
	gcc client_marshal.o marshal.o utils.o -o client

server_marshal.o: server_marshal.c
	gcc -c server_marshal.c

marshal.o: marshal.c
	gcc -c marshal.c

utils.o: utils.c
	gcc -c utils.c

client_marshal.o: client_marshal.c
	gcc -c client_marshal.c

clean:
	rm *.o server client
