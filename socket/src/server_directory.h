#ifndef GLOBAL_SERVER_DIRECTORY_H
#define GLOBAL_SERVER_DIRECTORY_H
#include "list.h"

struct arg_thread{
	int sock;			// the socket;
	struct node_l *head;	// the head node;
};

#endif