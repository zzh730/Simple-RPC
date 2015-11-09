CC=gcc

all: server client directory

server: server_marshal.o marshal.o utils.o
	gcc server_marshal.o marshal.o utils.o -o server

client: client_marshal.o marshal.o utils.o
	gcc client_marshal.o marshal.o utils.o -o client

directory: server_directory.o list.o entry.o mapper.o hashtable.o
	gcc -c server_directory.o list.o entry.o mapper.o hashtable.o

server_marshal.o: server_marshal.c
	gcc -c server_marshal.c

marshal.o: marshal.c
	gcc -c marshal.c

utils.o: utils.c
	gcc -c utils.c

client_marshal.o: client_marshal.c
	gcc -c client_marshal.c

server_directory.o: server_directory.c
	gcc -c server_directory.c

list.o:list.c
	gcc -c list.c

entry.o: entry.c
	gcc -c entry.c

mapper.o: mapper.c
	gcc -c mapper.c

hashtable.o: hashtable.c
	gcc -c hashtable.c

clean:
	rm *.o server client directory
