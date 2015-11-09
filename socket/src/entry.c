#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entry.h"

// void init_course(struct course* c, const char* id, int num_nodes)
// {
//     strncpy(c->identifier, id, sizeof(c->identifier));
//     c->num_nodes = num_nodes;
//     c->nodes = calloc(num_nodes, sizeof(struct node));
// }

// void init_entry(struct entry *en, char* ip_addr, int p_id, int p_version, int port_num){
// 	printf("the length of ip_addr is %lu\n", strlen(ip_addr));
// 	struct entry *ent = (struct entry*)malloc(sizeof(struct entry));
// 	*ent->ip_addr = "eifjsl";
// 	// printf("the length of ent->ip_addr is %lu\n", strlen(ent->ip_addr));
// 	// char am[30];
// 	// en->ip_addr = am;
// 	strncpy(ent->ip_addr, ip_addr, strlen(ip_addr));
// 	// en->p_id = p_id;
// 	// en->p_version = p_version;
// 	// en->port_num = port_num;
// }


int main(){
	struct entry *en = NULL;
	char *ip_addr = "192.166.2.2.";
	printf("yeahd\n");
	int p_id = 10;
	int p_version = 0;
	int port_num = 20;
	init_entry(en, ip_addr, p_id, p_version, port_num);
	// printf("the ip_addr is %s\n", en->ip_addr);
}