#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>


#define BUFFER_SIZE 128
#define PORTNO 8888

// function to perform on server
void dostuff(int);

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{   
    int sockfd, newsockfd, portno, pid;
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
    // listen 
    if ( listen(sockfd,5) != 0)
    {
        perror("ERROR on listen");
        exit(errno);

    }

    // accept client connection
    while(1)
    {   
        int clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)
        {
            close(sockfd);
            dostuff(newsockfd);
            close(newsockfd);
            exit(0);

        }
        close(newsockfd);
    }
    close(sockfd);
    
    return 0;
}


void dostuff(int sock)
{
    int n;
    char buffer[BUFFER_SIZE];

    bzero(buffer, BUFFER_SIZE);
    n = read(sock, buffer, BUFFER_SIZE);
    if (n < 0)
        error("ERROR reading from socket");

    printf("Here is the message: %s", buffer);

    // replay info
    n = write(sock, "ack", 18);
    if (n < 0) error("ERROR writing to socket");
}