#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapper.h"
#include "entry.h"
#ifndef COMMON_INCLUDE_FILE
#define COMMON_INCLUDE_FILE
#define BUFFER_SIZE 9999
#endif
//set a global header node	
// struct node_l *head=NULL;							//> always keep the head not null;
													//> in order to make an dynamic head node

// struct *node_l cHead(){
// 	head = creatHead();
// 	return head;
// }

// modified add function.

int service_add(struct node_l *head, struct entry *ent){
	// int flag = list_enqueue(head, ent);
	printf("The size of entry is: %lu\n", sizeof(struct entry));
	// struct entry *en = (struct entry*)malloc(sizeof(struct entry));
	struct node_l *node;
	struct entry *en = (struct entry*)malloc(sizeof(struct entry));
	node->next = NULL;
	node->elem = ent;
	struct node_l *current  = head;
	while(current->next!=NULL){
		current = current->next;
	}
	current->next = node;
	return 1;
}

int service_del(struct node_l *head, query_s *query){
	struct node_l *current = head;
	while(current->next!=NULL){
		struct entry *this_entry = (struct entry*)(current->next)->elem;
		if(this_entry->p_id==query->p_id && this_entry->p_version==query->p_version){
			current->next = list_dequeue(current->next);
			return 1;
		}
		current = current->next;
	}
	return 0;
}

port_s *find_add(struct node_l *head, query_s *query){
	struct node_l *current = head;
	while(current->next!=NULL){
		struct entry *this_entry = (struct entry*)(current->next)->elem;
		if(this_entry->p_id==query->p_id && this_entry->p_version==query->p_version){
			port_s *port_res = (port_s*)malloc(1*sizeof(port_s));
			port_res->flag = 1;
			printf("the ip address is %s\n", this_entry->ip_addr);
			printf("=================The length of the ip_add is %lu\n", strlen(this_entry->ip_addr));
			strncpy(port_res->ip_addr, this_entry->ip_addr, strlen(port_res->ip_addr));			// I have no idea why+1
			printf("the ip address is %s\n", this_entry->ip_addr);
			port_res->port_num = this_entry->port_num;
			return port_res;
		}
		current = current->next;
	}
	port_s *port_res = (port_s*)malloc(1*sizeof(port_s));
	port_res->flag = 0;
	// port_res->ip_addr = invalid
	port_res->port_num = 0;
	return port_res;
}


char *compression(int id, int version, char *addr, int port_num){
	struct entry *en = (struct entry*)malloc(sizeof(struct entry));
	en->p_id = id;
	en->p_version = version;
	en->ip_addr = addr;
	en->port_num = port_num;
	// printf("the size of ip_addr is:%lu\n", sizeof(*(en->ip_addr)));
	static char buffer[BUFFER_SIZE];
	int size = strlen(en->ip_addr);
	int csize = 4;
	memcpy(buffer, &size, size);
	memcpy(csize+buffer, &en->p_id, sizeof(en->p_id));
	memcpy(csize+buffer+sizeof(en->p_id), &en->p_version, sizeof(en->p_version));
	memcpy(csize+buffer+sizeof(en->p_id)+sizeof(en->p_version), en->ip_addr, strlen(en->ip_addr));
	memcpy(csize+buffer+sizeof(en->p_id)+sizeof(en->p_version)+strlen(en->ip_addr),\
	 &en->port_num, sizeof(en->port_num));
	return buffer;
}

struct entry *decompression(char *buffer){
	struct entry *res = (struct entry*)malloc(sizeof(struct entry));
	int resize = 0;
	int len_size = sizeof(resize);
	resize = *(int*)memcpy(&resize, buffer, sizeof(resize));
	// printf("The resize is :%d\n", resize);
	res->p_id = *(int*)memcpy(&(res->p_id), len_size+buffer, sizeof(res->p_id));
	res->p_version = *(int*)memcpy(&(res->p_version), len_size+buffer+sizeof(res->p_id), sizeof(res->p_version));
	char temp[100];
	bzero(temp, 100);			// must do it! otherwise it is not clear
	res->ip_addr = temp;
	res->ip_addr = (char*)memcpy(res->ip_addr, len_size+buffer+sizeof(res->p_id)+sizeof(res->p_version), resize);
	res->port_num = *(int*)memcpy(&(res->port_num), len_size+buffer+sizeof(res->p_id)+sizeof(res->p_version)+resize,\
	 sizeof(res->port_num));

	// printf("p->id=: %d\n", res->p_id);
	// printf("p->p_version=: %d\n", res->p_version);
	// printf("The length of the return string is:%lu\n", strlen(res->ip_addr));
	// printf("p->ip_addr=: %s\n", res->ip_addr);
	// printf("p->port_num= %d\n", res->port_num);

	return res;
}

// > Debug

// int main(){
// 	struct node_l *head = creatHead();
// 	if(head!=NULL){
// 		printf("The head created successfully!\n");
// 	}
// 	else{
// 		printf("The head is not created!\n");
// 	}
// 	//==========================================
// 	struct entry * first_n = (struct entry*)malloc(sizeof(struct entry));
// 	first_n->p_id = 0;
// 	first_n->p_version = 10;
// 	first_n->ip_addr = "192.162.2.1";
// 	first_n->port_num = 100;


// 	struct entry * sec_n = (struct entry*)malloc(sizeof(struct entry));
// 	sec_n->p_id = 2;
// 	sec_n->p_version = 20;
// 	sec_n->ip_addr = "222.162.2.1";
// 	sec_n->port_num = 50;

// 	if(service_add(head, first_n)==1){
// 		printf("Add 1 succ!\n");
// 	}else{
// 		printf("Add 1 failed!\n");
// 	}

// 	if(service_add(head, sec_n)==1){
// 		printf("Add 2 succ!\n");
// 	}else{
// 		printf("Add 2 failed!\n");
// 	}
// 	//==============================================
// 	query_s *q = (query_s *)malloc(1*sizeof(query_s));
// 	q->p_id = 2;
// 	q->p_version = 20;
// 	port_s *p_s = find_add(head, q);
// 	printf("port_s->ip_addr=%s\n", p_s->ip_addr);
// 	printf("port_s->port_num=%d\n", p_s->port_num);
// 	printf("port-s->flag=%d\n", p_s->flag);

// 	p_s = find_add(head, q);
// 	printf("port_s->ip_addr=%s\n", p_s->ip_addr);
// 	printf("port_s->port_num=%d\n", p_s->port_num);
// 	printf("port-s->flag=%d\n", p_s->flag);

// 	p_s = find_add(head, q);
// 	printf("port_s->ip_addr=%s\n", p_s->ip_addr);
// 	printf("port_s->port_num=%d\n", p_s->port_num);
// 	printf("port-s->flag=%d\n", p_s->flag);	
// 	//================================================
// 	query_s *qq = (query_s *)malloc(1*sizeof(query_s));
// 	qq->p_id = 2;
// 	qq->p_version = 20;
// 	if(service_del(head,qq)==1){
// 		printf("delete succ!\n");
// 	}else{
// 		printf("delete failed\n");
// 	}


// 	query_s *qm = (query_s *)malloc(1*sizeof(query_s));
// 	qm->p_id = 0;
// 	qm->p_version = 10;


// 	p_s = find_add(head, qm);
// 	printf("port_s->ip_addr=%s\n", p_s->ip_addr);
// 	printf("port_s->port_num=%d\n", p_s->port_num);
// 	printf("port-s->flag=%d\n", p_s->flag);


// }