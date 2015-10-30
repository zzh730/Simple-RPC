#ifndef GLOBAL_MAPPER_H
#define GLOBAL_MAPPER_H
#include "list.h"
#define LENGTH_IP 30


// Design the return struct to the client;
struct portadd{
	int flag;						//< flag = 0 if the service not exist; flag=1 otherwise;
	char *ip_addr;		//< the ip address in the return structure
	int port_num;					//< the port number 
};

struct query{
	int p_id;						//<	program id
	int p_version;					//< the version of the service;
};

typedef struct portadd port_s;
typedef struct query query_s;

int service_add(struct node_l *head, struct entry *ent);	//<	add a service if it is true, return 1, otherwise return 0;

int service_del(struct node_l *head,query_s *que);	//<	delete services with specification entry;

port_s *find_add(struct node_l *head, query_s *query);	//< make a query and get the port address together with the ipaddr

char *compression(int id, int version, char *addr, int port_num);	//> compress the entry struct into a buffer

struct entry *decompression(char *buffer);						//> unpack the buffer into an entry
#endif