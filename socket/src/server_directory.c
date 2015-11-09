#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h> //strlen
#include <arpa/inet.h> //inet_addr
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h> // write
#include <pthread.h> // threading
// Modified by Yingjie Tnag
#include "list.h"
#include "mapper.h"
#include "entry.h"
#include "server_directory.h"



#define BUFFER_SIZE 9999
#define PORTNO 8887                     //> used for directory server

// function to perform on server
void dostuff(int);
void *connection_handler(void *);

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{   
    int sockfd, newsockfd, portno;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    struct arg_thread *argthread;
    struct arg_thread *new_sock;

    // if (argc < 2)
    // {
    //     fprintf(stderr, "ERROR, no port provided\n");
    //     exit(1);
    // }
    //set the socket using unix address space and tcp/ip protocol
    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error ("EOORO opening socket");
        exit(errno);
    }
    puts("Socket created");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    // set the server addrass 
    portno = PORTNO;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
        exit(errno);

    } 
    puts("Bind finished");


    // listen 
    if ( listen(sockfd,5) != 0)
    {
        perror("ERROR on listen");
        exit(errno);

    }
    puts("Waiting for connection");
    //Build up the head node;
    struct node_l *head = NULL;
    head = creatHead();
    // struct node_l *first = (struct node_l*)malloc(sizeof(struct node_l));
    // struct entry *ent = (struct entry*)malloc(sizeof(struct entry));
    // ent->p_id = 1;
    // ent->p_version = 1;
    // ent->ip_addr = "2222222";
    // ent->port_num = 1;
    // first->next = NULL;
    // first->elem = ent;
    // head->next = first;
    // query_s *query = (query_s*)malloc(sizeof(query_s));
    // query->p_id = 0;
    // query->p_version = 10;
    // port_s *port = (port_s*)malloc(100);
    // port = find_add(head, query);
    // printf("========================\n");
    // printf("port->ip_addr=: %s\n", port->ip_addr);
    // printf("port->portno=: %d\n", port->port_num);

    // accept client connection
    while(1)
    {   
        int clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        //print out client ip address and port
        puts("Connection established");

        printf("%s:%d connected\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
        
        pthread_t sniffer_thread;
        argthread = (struct arg_thread*)malloc(sizeof(struct arg_thread));
        argthread->sock = newsockfd;
        argthread->head = head;
        new_sock = malloc(1);
        *new_sock = *argthread;


        // fill the arg_thread struct
        // struct 


        if (pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("ERROR on creating thread");
            exit(errno);

        }
        puts("Handler assigned");

        
    }
    close(sockfd);
    return 0;
}


void *connection_handler(void *socket_desc)
{
    //Instead of Get the socket descriptor, we get the struct
    struct arg_thread *myarg = (struct arg_thread*)socket_desc;
    int sock = myarg->sock;
    struct node_l *head = myarg->head;
    int read_size;
    char *message , client_message[2000];
     
    //Send some messages to the client
    message = "Connectation with server established \n";
    write(sock , message , strlen(message));
     
    //Receive a message from client
    if( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //end of string marker
        client_message[read_size] = '\0';
        printf("%s",client_message);
        printf("The length of the coming buffer is:%d\n", read_size);
        struct entry *myentry = decompression(client_message);
        printf("myentry->p_id: %d\n", myentry->p_id);
        printf("myentry->p_version: %d\n", myentry->p_version);
        printf("myentry->addr: %s\n", myentry->ip_addr);
        printf("myentry->port_num: %d\n", myentry->port_num);
        printf("==================================\n");
        //Send the message back to client
        // write(sock , client_message , strlen(client_message));
        // Add a node to the head;
        // service_add(head, myentry);
        //  manually add 
        struct node_l *sec_node = (struct node_l*)malloc(sizeof(struct node_l));
        sec_node->elem = myentry;
        sec_node->next =NULL;
        head ->next = sec_node;




        //============
        int num = list_count(head);
        printf("The list_count is:%d\n", num);

        // int i = 0;
        // while(head!=NULL){
        //     printf("i= %d\n", ++i);
        //     head = head->next;
        // }


        query_s *query = (query_s*)malloc(sizeof(query_s));
        query->p_id = 0;
        query->p_version = 10;
        port_s *port = (port_s*)malloc(sizeof(port_s));
        port = find_add(head, query);
        printf("========================\n");
        printf("port->ip_addr=: %s\n", port->ip_addr);
        printf("port->portno=: %d\n", port->port_num);
        printf("========================\n");
        struct entry *sec_entry = (struct entry*)malloc(sizeof(struct entry));
        sec_entry = (struct entry*)(head->next->elem);

        printf("port->ip_addr: %s\n", sec_entry->ip_addr);
        printf("port->port_num: %d\n", sec_entry->port_num);

        
        //clear the message buffer
        memset(client_message, 0, 2000);
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    free(socket_desc);

    return 0;
} 



