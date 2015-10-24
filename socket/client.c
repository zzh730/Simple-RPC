#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define BUFFER_SIZE 128

void error(char *msg)
{
    perror(msg);
    exit(0);
}

// argv[0]: 
// argv[1]: name of the host eg cs.pitt.edu
// argv[2]: port number 

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFFER_SIZE];
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);

    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
        exit(errno);
    }

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);

    }

    // set field in serv_addr
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
        exit(errno);

    }    

    // testing, send msg to server
    printf("Enter msg to server: ");
    bzero(buffer, BUFFER_SIZE);
    fgets(buffer, BUFFER_SIZE - 1, stdin);
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {    
        error("ERROR wrtiting to socket");
        exit(errno);
    }
    
    bzero(buffer, BUFFER_SIZE);
    n = read(sockfd,buffer, BUFFER_SIZE);
    if (n < 0)
    {    error("ERROR reading from socket");
        exit(errno);
    }
    printf("%s",buffer);
    close(sockfd);

    return 0;
}