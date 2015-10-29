#ifndef GLOBAL_MARSHAL_H
#define GLOBAL_MARSHAL_H


#define BUFFER_SIZE 9999

typedef struct 
{
    int id; 
    int number;
    char data[BUFFER_SIZE];
} Packet;


int processwc(int fd, int selfid);
int marshalwc(int sockfd, int id, int number, char *str);
int unmarshalwc(int sockfd);
void error(char *msg);

#endif