#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include "marshal.h"




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
        fgets(buffer, BUFFER_SIZE - 1, stdin);
        // n = write(sockfd, buffer, strlen(buffer));

        // if (n < 0)
        // {    
        //     error("ERROR wrtiting to socket");
        //     exit(errno);
        // }
// //---------word count--------------
//         bzero(buffer, BUFFER_SIZE);
//         n = marshalwc(sockfd, 1,1,"asdf sdfa fsdfg sdf");
//         if (n < 0)
//             error("ERROR when marshalling!");
        
//         n = read(sockfd,buffer, BUFFER_SIZE);
//         if (n < 0)
//         {    
//             error("ERROR reading from socket");
//         }
//         int wordcount = unmarshalwc(sockfd);
// //---------word count--------------

//---------min()-----------        
    //     bzero(buffer, BUFFER_SIZE);
    //     int arr[] = {1,2,3,4,5000,6,7,8,-9999,0};
    //     n = marshalmin(sockfd, 1,1,10, arr);
    //     if (n < 0)
    //     {
    //         error("ERROR: marshalling data");

    //     }
    //     bzero(buffer, BUFFER_SIZE);
    //     int min_num = unmarshalmin(sockfd);
    //     if (n < 0)
    //     {    
    //         error("ERROR unmarshal array in client");
    //     }
// //---------max()--------
//     bzero(buffer, BUFFER_SIZE);
//     int arr[] = {1,2,3,4,5000,6,7,8,-9999,0};
//     n = marshalmax(sockfd, 1,1,10, arr);
//     if (n < 0)
//     {
//         error("ERROR: marshalling data");

//     }

//     bzero(buffer, BUFFER_SIZE);
//     int max_num = unmarshalmax(sockfd);
//     if (n < 0)
//     {    
//         error("ERROR unmarshal array in client");
//     }
// ----max()----------  
//-----sort()--------
    // bzero(buffer, BUFFER_SIZE);
    // int arr[] = {1,2,3,4,5000,6,7,8,-9999,0};

    // n = marshalsort(sockfd, 1,1,10, arr);
    // if (n < 0)
    // {
    //     error("ERROR: marshalling data");

    // }

    // bzero(buffer, BUFFER_SIZE);
    // int *newarr =(int *) malloc(10*sizeof(int));
    // newarr = unmarshalsort(sockfd,10);
    // if (n < 0)
    // {    
    //     error("ERROR unmarshal array in client");
    // }
//-------------------
    int arr[3][4]  = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12}
    }; 
    n = marshal2darr(sockfd, 1, 1, 3,4,arr);
    if (n < 0){
        error("ERROR: marshal 2d array");

    }
    int B[4][5] = {
        {1,2,3,4,5},
        {6,7,8,9,10},
        {11,12,13,14,15},
        {16,17,18,19,20}
    };
    n = marshal2darr(sockfd, 1, 1, 4,5,B);
    if (n < 0){
        error("ERROR: marshal 2d array");

    }
    int C[5][3]={
        {1,2,3},
        {4,5,6},
        {7,8,9},
        {10,11,12},
        {13,14,15}
    };
    n = marshal2darr(sockfd, 1, 1, 5,3,C);
    if (n < 0){
        error("ERROR: marshal 2d array");

    }
    
    int  newarr[3][3];
    n = unmarshal2darr(sockfd,3,3,newarr);
    if (n < 0){
        error("ERROR: unmarshal 2d array");

    }
    //free(newarr);

    }


//---------------------------
    return 0;
}