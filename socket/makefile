CC=gcc
CCFLAGS=-std=c11 -lm -D_GNU_SOURCE



all: server client directory

server: server_marshal.o marshal.o utils.o
	${CC} ${CCFLAGS} server_marshal.o marshal.o utils.o -o server -lpthread

client: client_marshal.o marshal.o utils.o
	${CC} ${CCFLAGS} client_marshal.o marshal.o utils.o -o client

directory: server_directory.o list.o entry.o mapper.o hashtable.o
	${CC} ${CCFLAGS} -c server_directory.o list.o entry.o mapper.o hashtable.o

server_marshal.o: server_marshal.c
	${CC} ${CCFLAGS} -c server_marshal.c -lpthread

marshal.o: marshal.c
	${CC} ${CCFLAGS} -c marshal.c

utils.o: utils.c
	${CC} ${CCFLAGS} -c utils.c

client_marshal.o: client_marshal.c
	${CC} ${CCFLAGS} -c client_marshal.c

server_directory.o: server_directory.c
	${CC} ${CCFLAGS} -c server_directory.c

list.o:list.c
	${CC} ${CCFLAGS} -c list.c

entry.o: entry.c
	${CC} ${CCFLAGS} -c entry.c

mapper.o: mapper.c
	${CC} ${CCFLAGS} -c mapper.c

hashtable.o: hashtable.c
	${CC} ${CCFLAGS} -c hashtable.c

clean:
	rm *.o *.c *.h server client directory

