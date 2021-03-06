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
    Packet_Str *s = malloc(sizeof(Packet_Str));
    memset(s->data, 0, sizeof(s->data));
    s->id = htonl(id);
    s->number = htonl(number);
    // printf("stirng:%s\n", str);
    memcpy(s->data, str, strlen(str));
    s->data[strlen(str)] = '\0';
    // printf("sdata%s\n", s->data);
    n = write(sockfd, s, sizeof(Packet_Str));
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
    char buffer[sizeof(Packet_Str)];
    memset(buffer, 0, sizeof(buffer));
    n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0)
    {
        error("Error reading!");
        exit(errno);
    }
    Packet_Str *s = (Packet_Str *) buffer;
    printf("Word Count: %s\n", s->data);
    return atoi(s->data);
}    

int processwc(int sockfd, int self_id)
{
    int n;

    char buffer_here[sizeof(Packet_Str)];
    memset(buffer_here, 0, sizeof(buffer_here));
    n = read(sockfd, buffer_here, sizeof(buffer_here));
    if (n < 0)
    {
        error("Error reading!");
        exit(errno);
    }
    // printf("BUffer:%s\n", buffer_here);
    Packet_Str *s = (Packet_Str *)buffer_here;
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
        printf("DATA: %s\n",s->data);
        n = write(sockfd, s, sizeof(Packet_Str));
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
        int max_num = max(size,arr);
        n = send(sockfd, &max_num, sizeof(int),0);
    }
    else if (number == SORT)
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

int marshal2darr(int sockfd, int id, int number, int n, int m, int A[m*n])
{
    int re;
    // send m n struct first
    arr2d *s = malloc(sizeof(arr2d));
    s->id = htonl(id);
    s->number = htonl(number);
    s->n = htonl(n);
    s->m = htonl(m);
    re = write(sockfd, s, sizeof(arr2d));
    if (re < 0)
    {
        error("Error in writing m n");
    }
    free(s);
    char buffer[BUFFER_SIZE];
    if (read(sockfd, buffer, BUFFER_SIZE))
    {
        puts("Send 2d array to server");

        n = send(sockfd, A, m*n*sizeof(int),0);
        if (n < 0)
        {
            error("ERROR: sending 2d array from client");
        }
    }
    else{
        error("ERROR: server not creating array");
    } 
    return re;
}

int processmultiply(int sockfd, int self_id)
{
    int re;
// first
        char buffer_here[sizeof(arr2d)];
        memset(buffer_here, 0, sizeof(buffer_here));
        re = read(sockfd, buffer_here, sizeof(buffer_here));
        if (re < 0)
        {
            error("Error reading!");
        }

        arr2d *s1 = (arr2d *)buffer_here;
        // memset(s->data, 0, sizeof(s->data));

        int id1 = ntohl(s1->id);
        int number1 = ntohl(s1->number);
        int n1 = ntohl(s1->n);
        int m1 = ntohl(s1->m);
        printf("m:%d,n:%d\n ",m1,n1);
        char *ack1 = "Y";
        re = write(sockfd, ack1, strlen(ack1));
        if(re < 0)
            {
                error("ERROR: write ack to client");
            }
        int *temp1 = (int *) malloc(m1*n1*sizeof(int));
        re = recv(sockfd, temp1, m1*n1*sizeof(int), 0);
        if (re < 0)
        {
            error("ERROR: recv array from client");
        }
        for (int i = 0; i <m1*n1;i++)
        {
            printf("arr[%d]:%d ",i,temp1[i]);
        }
        int array1[n1][m1];
        for (int i = 0; i < m1*n1;i++)
        {

                array1[(int)i/m1][(int)i%m1]= temp1[i];

        }
        for (int i = 0; i < n1;i++)
        {
            for(int j = 0; j <m1; j++)
            {
                printf("arr[%d][%d]:%d ",i,j,array1[i][j]);
            }
        }
        free(temp1);
        

//second
        memset(buffer_here, 0, sizeof(buffer_here));
        re = read(sockfd, buffer_here, sizeof(buffer_here));
        if (re < 0)
        {
            error("Error reading!");
        }

        arr2d *s2 = (arr2d *)buffer_here;
        // memset(s->data, 0, sizeof(s->data));

        int id2 = ntohl(s2->id);
        int number2 = ntohl(s2->number);
        int n2 = ntohl(s2->n);
        int m2 = ntohl(s2->m);
        printf("m:%d,n:%d\n ",m2,n2);
        char *ack2 = "Y";
        re = write(sockfd, ack2, strlen(ack2));
        if(re < 0)
            {
                error("ERROR: write ack to client");
            }
        int *temp2 = (int *) malloc(m2*n2*sizeof(int));
        re = recv(sockfd, temp2, m2*n2*sizeof(int), 0);
        if (re < 0)
        {
            error("ERROR: recv array from client");
        }
        for (int i = 0; i <m2*n2;i++)
        {
            printf("arr[%d]:%d ",i,temp2[i]);
        }
        int array2[n2][m2];
        for (int i = 0; i < m2*n2;i++)
        {

            array2[(int)i/m2][(int)i%m2]= temp2[i];
            
        }
        for (int i = 0; i < n2;i++)
        {
            for(int j = 0; j <m2; j++)
            {
                printf("arr[%d][%d]:%d ",i,j,array2[i][j]);
            }
        }
        free(temp2);
//third
        memset(buffer_here, 0, sizeof(buffer_here));
        re = read(sockfd, buffer_here, sizeof(buffer_here));
        if (re < 0)
        {
            error("Error reading!");
        }

        arr2d *s3 = (arr2d *)buffer_here;
        // memset(s->data, 0, sizeof(s->data));

        int id3 = ntohl(s3->id);
        int number3 = ntohl(s3->number);
        int n3 = ntohl(s3->n);
        int m3 = ntohl(s3->m);
        printf("m:%d,n:%d\n ",m3,n3);
        char *ack3 = "Y";
        re = write(sockfd, ack3, strlen(ack3));
        if(re < 0)
            {
                error("ERROR: write ack to client");
            }
        int *temp3 = (int *) malloc(m3*n3*sizeof(int));
        re = recv(sockfd, temp3, m3*n3*sizeof(int), 0);
        if (re < 0)
        {
            error("ERROR: recv array from client");
        }
        for (int i = 0; i <m3*n3;i++)
        {
            printf("arr[%d]:%d ",i,temp3[i]);
        }
        int array3[n3][m3];
        for (int i = 0; i < m3*n3;i++)
        {
            array3[(int)i/m3][(int)i%m3] = temp3[i];
        }
        for (int i = 0; i < n3;i++)
        {
            for(int j = 0; j <m3; j++)
            {
                printf("arr[%d][%d]:%d ",i,j,array3[i][j]);
            }
        }
        free(temp3);
        int res[n1][m3];
        memset(res, 0, sizeof(res));
        multiply(n1,m1,m2,m3, array1,array2, array3,res);
        //shan
        int resarr[n1*m3];
        for (int i = 0;i<n1;i++)
        {
            for (int j = 0;j < m3;j++)
            {
                resarr[i*m3+j] = res[i][j];
            }
        }
        for (int i = 0;i < n1*m3; i++)
        {
            printf("res[%d]:%d",i,resarr[i]);

        }
// sent back result
// send m n struct of result back to client
    arr2d *p = malloc(sizeof(arr2d));
    p->id = htonl(id1);
    p->number = htonl(number1);
    p->n = htonl(n1);
    p->m = htonl(m3);
    re = write(sockfd, p, sizeof(arr2d));
    if (re < 0)
    {
        error("Error in writing m n");
    }
    free(p);
    char buffer[BUFFER_SIZE];
    if (read(sockfd, buffer, BUFFER_SIZE))
    {
        puts("Send 2d array to server");
        int temp[n1*m3];
        for (int i = 0; i < n1;i++)
        {
            for (int j = 0; j < m3; j++)
            {
                temp[i*m3+j] = res[i][j];
            }
        }
        re = send(sockfd, temp, n1*m3*sizeof(int),0);
        if (re < 0)
        {
            error("ERROR: sending 2d array from client");
        }
    }
    else{
        error("ERROR: server not creating array");
    } 

    return re;
    
    // printf("id:%d, num:%d, buf:%s\n",id,number,b);
}

int unmarshal2darr(int sockfd,int n, int m, int array[n][m])
{
    int re;

        char buffer_here[sizeof(arr2d)];
        memset(buffer_here, 0, sizeof(buffer_here));
        re = read(sockfd, buffer_here, sizeof(buffer_here));
        if (re < 0)
        {
            error("Error reading!");
        }

        arr2d *s = (arr2d *)buffer_here;
        // memset(s->data, 0, sizeof(s->data));

        int id = ntohl(s->id);
        int number = ntohl(s->number);
        n = ntohl(s->n);
        m = ntohl(s->m);
        printf("m:%d,n:%d\n ",m,n);
        char *ack = "Y";
        re = write(sockfd, ack, strlen(ack));
        if(re < 0)
            {
                error("ERROR: write ack to client");
            }
        int *temp = (int *) malloc(m*n*sizeof(int));
        re = recv(sockfd, temp, m*n*sizeof(int), 0);
        if (re < 0)
        {
            error("ERROR: recv array from client");
        }
        for (int i = 0; i <m*n;i++)
        {
            printf("arr[%d]:%d ",i,temp[i]);
        }
        for (int i = 0; i < m*n;i++)
        {

                array[(int)i/m][(int)i%m]= temp[i];

        }
        for (int i = 0; i < n;i++)
        {
            for(int j = 0; j <m; j++)
            {
                printf("arr[%d][%d]:%d ",i,j,array[i][j]);
            }
        }
        free(temp);
    return re;
}

