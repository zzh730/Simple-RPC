#ifndef GLOBAL_MARSHAL_H
#define GLOBAL_MARSHAL_H


#define BUFFER_SIZE 9999
#define MIN 1
#define MAX 2
#define SORT 3

typedef struct 
{
    int id; 
    int number;
    char data[BUFFER_SIZE];
} Packet_Str;

typedef struct 
{
    int id; 
    int number;
    int m;
    int n;
} arr2d;


int processwc(int fd, int selfid);
int marshalwc(int sockfd, int id, int number, char *str);
int unmarshalwc(int sockfd);

int marshalmin(int sockfd, int id, int number, int size, int *arr);
int unmarshalmin(int sockfd);
int processarray(int sockfd, int self_id, int number);

int marshalmax(int sockfd, int id, int number, int size, int *arr);
int unmarshalmax(int sockfd);

int marshalsort(int sockfd, int id, int number, int size, int *arr);
int *unmarshalsort(int sockfd, int size);

int marshal2darr(int sockfd, int id, int number, int n, int m, int A[n*m]);
int processmultiply(int sockfd, int self_id);
int unmarshal2darr(int sockfd, int n,int m,int res[n][m]);

void error(char *msg);

#endif