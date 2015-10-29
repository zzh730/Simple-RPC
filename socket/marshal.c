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
#include "utils.h"
#include "marshal.h"





void error(char *msg)
{
    perror(msg);
    exit(1);
}

//---------word count--------------
int marshalwc(int sockfd, int id, int number, char *str)
{
    int n;
    Packet *s = malloc(sizeof(Packet));
    memset(s->data, 0, sizeof(s->data));
    s->id = htonl(id);
    s->number = htonl(number);
    // printf("stirng:%s\n", str);
    memcpy(s->data, str, strlen(str));
    s->data[strlen(str)] = '\0';
    // printf("sdata%s\n", s->data);
    n = write(sockfd, s, sizeof(Packet));
    if (n < 0)
    {
        error("Error in writing");
        n = -1;
    }
    free(s);
    return n;
}

int unmarshalwc(int sockfd)
{
    int n;
    char buffer[sizeof(Packet)];
    memset(buffer, 0, sizeof(buffer));
    n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0)
    {
        error("Error reading!");
        exit(errno);
    }
    Packet *s = (Packet *) buffer;
    printf("Word Count: %s\n", s->data);
    return n;
}    

int processwc(int sockfd, int self_id)
{
    int n;

    char buffer_here[sizeof(Packet)];
    memset(buffer_here, 0, sizeof(buffer_here));
    n = read(sockfd, buffer_here, sizeof(buffer_here));
    if (n < 0)
    {
        error("Error reading!");
        exit(errno);
    }
    // printf("BUffer:%s\n", buffer_here);
    Packet *s = (Packet *)buffer_here;
    // memset(s->data, 0, sizeof(s->data));
    char b[BUFFER_SIZE];
    int id = ntohl(s->id);
    int number = ntohl(s->number);
    memcpy(b, s->data, BUFFER_SIZE*sizeof(char));
    // printf("id:%d, num:%d, buf:%s\n",id,number,b);
    if (id <= self_id){
        int count = wc(s->data);
        memset(s, 0, sizeof(*s));
        s->id = self_id;
        s->data[0] = count + '0';
        s->data[1] = '\0';
        n = write(sockfd, s, sizeof(*s));
        if (n < 0)
            error("Error in writing!");

    }
    else{
        char *reply = "Error: client version is higher than server!\n";
        printf("%s\n", reply);
        n = write(sockfd, reply, sizeof(reply));
        if (n < 0){
            error("Error writing");

        }
    }
    return n;

}
//---------word count--------------

// int marshalarray(int sockfd, int id, int number, int size, int *arr)
// {
//     int n;
//     Packet *s = malloc(sizeof(Packet));
//     memset(s->data, 0, sizeof(s->data));
//     s->id = htonl(id);
//     s->number = htonl(number);
//     // printf("stirng:%s\n", str);
//     memcpy(s->data, str, strlen(str));
//     s->data[strlen(str)] = '\0';
//     // printf("sdata%s\n", s->data);
//     n = write(sockfd, s, sizeof(Packet));
//     if (n < 0)
//     {
//         error("Error in writing");
//         n = -1;
//     }
//     free(s);
//     return n;
// }

