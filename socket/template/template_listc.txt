#include <stdlib.h>
#include <stdio.h>
#include "list.h"
/*Declaration of the method*/
void print_list(struct node_l * head) {
    struct node_l * current = head;
    while (current != NULL) {
    	struct entry *this_entry = (struct entry*)current->elem;
        printf("print_list: %d\n", this_entry->p_id);
        current = current->next;
    }
}




struct node_l *creatHead(){
	struct node_l *head = (struct node_l *)malloc(1*sizeof(struct node_l));
	head->next=NULL;
	return head;
}

int list_count(struct node_l *head){
	int res = 0;
	struct entry *abc;
	while(head!=NULL){
		res+=1;
		abc= (struct entry *)(head->elem);
		head = head->next;
	}
	return res;
	
}	

void *list_tail(struct node_l *head){
	if(head==NULL) return NULL;
	while(head->next!=NULL){
		head = head->next;
	}
	return head;
}

// int list_enqueue(struct node_l *head, void *element){
// 	struct node_l * current = list_tail(head);
// 	if(current==NULL) return 0;
// 	else{
// 		struct node_l * new_node = (struct node_l*)malloc(1*sizeof(struct node_l));
// 		new_node->elem = element;
// 		new_node->next = NULL;
// 		current->next = new_node;
// 		return 1;
// 	}
// }
//    modified the enqueue part
int list_enqueue(struct node_l *head, void *element){
	struct node_l * current = list_tail(head);
	if(current==NULL) return 0;
	else{
		struct node_l * new_node = (struct node_l*)malloc(1*sizeof(struct node_l));
		new_node->elem = element;
		new_node->next = NULL;
		current->next = new_node;
		return 1;
	}
}

void *list_dequeue(struct node_l *head){
	if(head==NULL){
		return NULL;
	}else{
		struct node_l *current = head;
		if(current!=NULL){
			if(current->elem!=NULL){
				free(current->elem);
				current->elem = NULL;
			}
			free(current);
			current = NULL;
		}
		head = head->next;
		return head;
	}
}

void *list_get(struct node_l *head, int idx){
	struct node_l *current = head;
	if(idx+1>list_count(head)){
		return NULL;
	}
	for(int i=0;i<idx;i++){
		current = current->next;
	}
	return current;
}	

void *list_next(struct node_l *head){
	if(head==NULL||head->next==NULL){
		return NULL;
	}else{
		return head->next;
	}
}


// int main(){

// 	struct node_l * head = creatHead();
// 	head->next = NULL;
// 	if (head == NULL) {
// 	    printf("Fail to create the head of the list!");
// 	    return 1;
// 	}else{
// 		printf("Created!\n");
// 	}
// 	int first = list_count(head);
// 	printf("The value of the first node is :%d\n", first);
// 	/* Create the head node */
// 	struct entry *my_entry = malloc(sizeof(struct entry));
// 	if(my_entry==NULL){
// 		return 1;
// 	}
// 	my_entry->p_id = 1;
// 	my_entry->p_version = 0;
// 	my_entry->ip_addr = "113.22.3.4";
// 	my_entry->port_num = 8086;
// 	head->elem = my_entry;
// 	head->next = NULL; 

// 	/* Show the elements of head */
// 	struct entry *this = (struct entry *)head->elem;
// 	printf("The p_id of entry is %d\n",this->p_id);
// 	// int first = list_count(head);
// 	// printf("The value of the first node is :%d\n", first);
// 	/* Create the second node */
// 	struct entry *sec_entry = malloc(sizeof(struct entry));
// 	if(sec_entry==NULL){
// 		return 1;
// 	}
// 	sec_entry->p_id = 2;
// 	sec_entry->p_version = 0;
// 	sec_entry->ip_addr = "113.22.3.4";
// 	sec_entry->port_num = 8086;

// 	// struct node_l *sec_node =  (struct node_l*)malloc(sizeof(struct node_l));
// 	// sec_node->elem = my_entry;
// 	// sec_node->next = NULL; 

// 	// enqueue method
// 	print_list(head);
// 	int flag = list_enqueue(head, sec_entry);
// 	print_list(head);
// 	// printf("The add method worked as %d\n", flag);
// 	int num = list_count(head);
// 	// printf("111111111");
// 	// printf("The length of the list is: %d\n", list_count(head));
// 	// printf("===============================\n");
// 	// print_list(head);
// 	// dequeue method;
// 	// head = list_dequeue(head);
// 	// head = list_dequeue(head);
// 	struct node_l *mynext = list_next(head);
// 	printf("The length of the list is: %d\n", list_count(head));
// 	printf("===============================\n");
// 	print_list(mynext);
// }


