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


#define BUFFER_SIZE 9999
#define PORTNO 8888

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
    int sockfd, newsockfd, portno, *new_sock;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;

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

    // accept client connection
    while(1)
    {   
        int clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        //print out client ip address and port
        puts("Connection established");

        printf("%s:%d connected\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
        
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = newsockfd;

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
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];
     
    //Send some messages to the client
    message = "Connectation with server established \n";
    write(sock , message , strlen(message));
     
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //end of string marker
        client_message[read_size] = '\0';
        
        //Send the message back to client
        write(sock , client_message , strlen(client_message));
        
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

