#ifndef GLOBAL_LIST_H
#define	GLOBAL_LIST_H
#include "entry.h"



struct node_l{
	struct entry *elem;
	struct node_l *next;
};

void print_list(struct node_l *head);

struct node_l *creatHead();		//Create the head node

int list_count(struct node_l *head);	//Count the nodes in the list

void *list_tail(struct node_l *head);	//Get the tail node of the list

int list_enqueue(struct node_l *head, void *elem);	//Add an element into the end of the list

void *list_dequeue(struct node_l *head);	// Delete the head of the lsit

void *list_get(struct node_l *head, int idx);	// Get the node in the exact index

void *list_next(struct node_l *head);	//	Get the next node of the list


#endif