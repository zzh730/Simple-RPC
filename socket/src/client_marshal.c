#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include "marshal.h"
#include "utils.h"
#include "list.h"
#include "mapper.h"

char funcselect()
{
    char selection;
    printf("Please select which function to run!:\n");
    printf("a. int WordCount(string str)\n");
    printf("b. int max(int size, int *array)\n");
    printf("c. int min(int size, int *array)\n");
    printf("d. int *sort(int size, int *array)\n");
    printf("e. void multiply(int n, int m, int l, int A[n][m], int B[m][l], int C[l][n], int res[n][n])\n");
    scanf("%c", &selection);
    return selection;

}


int inputsize()
{
    int size;
    printf("Please enter the size of the array\n");
    scanf("%d", &size);
    return size;
}

int *input1darr(int size)
{
    int arr[size];
    printf("Please enter the array\n");
    for (int i = 0;i < size;i++)
    {
        scanf("%d", &arr[i]);

    }
    return arr;

}

int *input2darr(int m, int n)
{
    int arr[m*n];
    printf("Please the element of array\n");
    for (int i = 0; i < m*n; i++)
    {
        scanf("%d", &arr[i]);

    }
    return arr;
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
        error("ERROR");
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
        
    }

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        error("ERROR");

    }

    // set field in serv_addr
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    
    }    
    while(1)
    {   
        // testing, send msg to server
        printf("Enter msg to server: \n");
        bzero(buffer, BUFFER_SIZE);

        n = read(sockfd, buffer, strlen(buffer));
        if(n<0)
        {
            error("ERROR: reading from server");
        }
        printf("Message from server: %s\n", buffer);

        // if (n < 0)
        // {    
        //     error("ERROR wrtiting to socket");
        //     exit(errno);
        // }

        char sel = funcselect();
        n = send(sockfd, (void *) &sel,sizeof(char),0);
        if(n<0)
        {
            error("ERROR: sending function number");

        }
        switch( sel ) 
        {
            case 'a':
                {   

                    bzero(buffer, BUFFER_SIZE);
                    printf("Please enter the string\n");
                    getchar();

                    char str[1024];
                    fgets(str, 1024, stdin);
                    n = marshalwc(sockfd, 1,1,str);
                    if (n < 0)
                        error("ERROR when marshalling!");
                    int wordcount = unmarshalwc(sockfd);
                    printf("result is: %d\n",wordcount);
                    if (n < 0)
                        error("ERROR when unmarshalling!");
                    break;
                }
            case 'b':
                {
                    bzero(buffer, BUFFER_SIZE);
                    //int size = inputsize();
                    int arr_size = inputsize();
                    int *arr = input1darr(arr_size);
                    n = marshalmax(sockfd, 1,2, arr_size, arr);
                    if (n < 0)
                    {
                        error("ERROR: marshalling data");

                    }

                    bzero(buffer, BUFFER_SIZE);
                    int max_num = unmarshalmax(sockfd);
                    if (n < 0)
                    {    
                        error("ERROR unmarshal array in client");
                    }
                    break;
                }
            case 'c':
            {
                bzero(buffer, BUFFER_SIZE);

                int arr_size = inputsize();
                int *arr = input1darr(arr_size);
                n = marshalmin(sockfd, 1,3, arr_size, arr);
                if (n < 0)
                {
                    error("ERROR: marshalling data");

                }
                bzero(buffer, BUFFER_SIZE);
                int min_num = unmarshalmin(sockfd);
                if (n < 0)
                {    
                    error("ERROR unmarshal array in client");
                }
                break;
            }
            case 'd':
            {
                bzero(buffer, BUFFER_SIZE);
                int arr_size = inputsize();
                int *arr = input1darr(arr_size);
                n = marshalsort(sockfd, 1,4,arr_size, arr);
                if (n < 0)
                {
                    error("ERROR: marshalling data");

                }

                bzero(buffer, BUFFER_SIZE);
                int *newarr =(int *) malloc(10*sizeof(int));
                newarr = unmarshalsort(sockfd,10);
                if (n < 0)
                {    
                    error("ERROR unmarshal array in client");
                }
                free(newarr);
                break;

            }
            case 'e':
                {
                    int m1,n1,m2,n2,m3,n3;
                    int *arr1, *arr2,*arr3;
                    printf("Please enter the size of the row\n");
                    scanf("%d", &m1);
                    printf("Please enter the size of the column\n");
                    scanf("%d", &n1);
                    arr1 = input2darr(m1,n1);
                    n = marshal2darr(sockfd, 1, 5, m1,n1,arr1);
                    if (n < 0){
                        error("ERROR: marshal 2d array");

                    }
                    printf("Please enter the size of the row\n");
                    scanf("%d", &m2);
                    printf("Please enter the size of the column\n");
                    scanf("%d", &n2);
                    arr2 = input2darr(m2,n2);
                    n = marshal2darr(sockfd, 1, 5, m2,n2,arr2);
                    if (n < 0){
                        error("ERROR: marshal 2d array");

                    }
                    printf("Please enter the size of the row\n");
                    scanf("%d", &m3);
                    printf("Please enter the size of the column\n");
                    scanf("%d", &n3);
                    arr3 = input2darr(m3,n3);
                    n = marshal2darr(sockfd, 1, 5, m3,n3,arr3);
                    if (n < 0){
                        error("ERROR: marshal 2d array");

                    }
                    
                    int  newarr[m1][n3];
                    n = unmarshal2darr(sockfd,m1,n3,newarr);
                    if (n < 0){
                        error("ERROR: unmarshal 2d array");

                    }
                    break;
                }

            default :
                error("Can not read the value");
        }

    //free(newarr);

    }

    return 0;
}

