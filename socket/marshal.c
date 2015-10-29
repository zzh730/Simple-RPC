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
// int marshalwc(int sockfd, int id, int number, char *str)
// {
//     int n;
//     Packet_Str *s = malloc(sizeof(Packet_Str));
//     memset(s->data, 0, sizeof(s->data));
//     s->id = htonl(id);
//     s->number = htonl(number);
//     // printf("stirng:%s\n", str);
//     memcpy(s->data, str, strlen(str));
//     s->data[strlen(str)] = '\0';
//     // printf("sdata%s\n", s->data);
//     n = write(sockfd, s, sizeof(Packet_Str));
//     if (n < 0)
//     {
//         error("Error in writing");
//         n = -1;
//     }
//     free(s);
//     return n;
// }

// int unmarshalwc(int sockfd)
// {
//     int n;
//     char buffer[sizeof(Packet_Str)];
//     memset(buffer, 0, sizeof(buffer));
//     n = read(sockfd, buffer, sizeof(buffer));
//     if (n < 0)
//     {
//         error("Error reading!");
//         exit(errno);
//     }
//     Packet_Str *s = (Packet_Str *) buffer;
//     printf("Word Count: %s\n", s->data);
//     return s->data;
// }    

// int processwc(int sockfd, int self_id)
// {
//     int n;

//     char buffer_here[sizeof(Packet_Str)];
//     memset(buffer_here, 0, sizeof(buffer_here));
//     n = read(sockfd, buffer_here, sizeof(buffer_here));
//     if (n < 0)
//     {
//         error("Error reading!");
//         exit(errno);
//     }
//     // printf("BUffer:%s\n", buffer_here);
//     Packet_Str *s = (Packet_Str *)buffer_here;
//     // memset(s->data, 0, sizeof(s->data));
//     char b[BUFFER_SIZE];
//     int id = ntohl(s->id);
//     int number = ntohl(s->number);
//     memcpy(b, s->data, BUFFER_SIZE*sizeof(char));
//     // printf("id:%d, num:%d, buf:%s\n",id,number,b);
//     if (id <= self_id){
//         int count = wc(s->data);
//         memset(s, 0, sizeof(*s));
//         s->id = self_id;
//         s->data[0] = count + '0';
//         s->data[1] = '\0';
//         n = write(sockfd, s, sizeof(*s));
//         if (n < 0)
//             error("Error in writing!");

//     }
//     else{
//         char *reply = "Error: client version is higher than server!\n";
//         printf("%s\n", reply);
//         n = write(sockfd, reply, sizeof(reply));
//         if (n < 0){
//             error("Error writing");

//         }
//     }
//     return n;

// }
//---------word count--------------

int marshalmin(int sockfd, int id, int number, int size, int *arr)
{
    int n;
    //sent the size first 
    n = send(sockfd, &size, sizeof(int),0);
    if (n < 0){
        error("ERROR in Sending sizd of array!");

    }
    char buffer[BUFFER_SIZE];
    
    if (read(sockfd, buffer, BUFFER_SIZE))
    {
        puts("sent array to server");
        n = send(sockfd, arr, size*sizeof(int),0);
        if (n < 0)
        {
            error("ERROR: sending array from client");
        }
    }
    else{
        error("ERROR: server not creating array");
    }

   
    return n;
}

int unmarshalmin(int sockfd)
{
    int n,min_num;
    n = recv(sockfd, (void *) &min_num, sizeof(int),0);  
    if (n < 0)  
    {
        error("ERROR: receiving from server");

    }
    printf("Min: %d\n", min_num);
    return min_num;
} 

int processarray(int sockfd, int self_id, int number)
{
    int size= 0;
    int n;
    n = recv(sockfd, (void *)&size, sizeof(int),0);
    printf("size:%d",size);
    //printf("client:%d\n", *size);
    if (n < 0)
    {
        error("ERROR: reading array size in server");

    }
    char *ack = "Y";
    n = write(sockfd, ack, strlen(ack));
    if(n < 0)
        {
            error("ERROR: write ack to client");

        }
    int *arr = (int *) malloc(size*sizeof(int));
    n = recv(sockfd, arr, size*sizeof(int), 0);
    if (n < 0)
    {
        error("ERROR: recv array from client");
    }
    for (int i = 0; i <size;i++)
    {
        printf("arr[%d]:%d\n",i,arr[i]);
    }

    if (number == MIN)
    {
        int min_num = min(size, arr);
        n = send(sockfd, &min_num, sizeof(int),0);
    }
    else if (number == MAX)
    {       
        for (int i = 0; i < size; ++i)
        {
            for (int j = i + 1; j < size; ++j)
            {
                if (arr[i] > arr[j])
                {
                    int a =  arr[i];
                    arr[i] = arr[j];
                    arr[j] = a;
                }
            }
        }
        int max_num = max(size,arr);
        n = send(sockfd, &max_num, sizeof(int),0);
    }
    else if (number == SORT)
    {
        n = send(sockfd, arr, size*sizeof(int),0);
        if(n< 0)
        {
            error("ERROR: send array back to client");

        }
    }
    else{
        error("ERROR: unknown instructure for array");

    }
    if (n < 0)
    {
        error("ERROR: sent back result to client");

    }
    
    free(arr);


    return n;

}

int marshalmax(int sockfd, int id, int number, int size, int *arr)
{
    int n;
    //sent the size first 
    n = send(sockfd, &size, sizeof(int),0);
    if (n < 0){
        error("ERROR in Sending sizd of array!");

    }
    char buffer[BUFFER_SIZE];
    
    if (read(sockfd, buffer, BUFFER_SIZE))
    {
        puts("sent array to server");
        n = send(sockfd, arr, size*sizeof(int),0);
        if (n < 0)
        {
            error("ERROR: sending array from client");
        }
    }
    else{
        error("ERROR: server not creating array");
    }

   
    return n;
}

int unmarshalmax(int sockfd)
{
    int n,max_num;
    n = recv(sockfd, (void *) &max_num, sizeof(int),0);  
    if (n < 0)  
    {
        error("ERROR: receiving from server");

    }
    printf("Max: %d\n", max_num);
    return max_num;
}


int marshalsort(int sockfd, int id, int number, int size, int *arr)
{
    int n;
    //sent the size first 
    n = send(sockfd, &size, sizeof(int),0);
    if (n < 0){
        error("ERROR in Sending sizd of array!");

    }
    char buffer[BUFFER_SIZE];
    
    if (read(sockfd, buffer, BUFFER_SIZE))
    {
        puts("sent array to server");
        n = send(sockfd, arr, size*sizeof(int),0);
        if (n < 0)
        {
            error("ERROR: sending array from client");
        }
    }
    else{
        error("ERROR: server not creating array");
    }

   
    return n;
}

int *unmarshalsort(int sockfd, int size)
{
    int n;
    int *arr =(int *) malloc(size*sizeof(int));
    n = recv(sockfd, arr, size*sizeof(int),0);  
    if (n < 0)  
    {
        error("ERROR: receiving from server");

    }
    for (int i =0;i< size;i++)
    {
        printf("a[%d]:%d\n",i,arr[i]);

    }
    return arr;
}
