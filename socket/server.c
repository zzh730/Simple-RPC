#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int BUFFER_SIZE = 256;


void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    //set the socket using unix address space and tcp/ip protocol
    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error ("EOORO opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    // set the server addrass 
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin)addr.s_addr = INADDR_ANY;
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // listen 
    listen(sockfd,5);

    // accept client connection
    clien = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    // read from client
    bzero(buffer, BUFFER_SIZE);
    n = read(newsockfd, buffer, BUFFER_SIZE - 1);
    if (n < 0) error ("ERROR reading from the socket");
    printf("Here is the message: %s", buffer);

    // replay info
    n = write(newsockfd, "ack", 18);
    if (n < 0) error("ERROR writing to socket");

    return 0;
}