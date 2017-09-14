#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<strings.h>
#include<stdio.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <iostream>
using namespace std;


int main(){
    
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    
    server.sin_family= AF_INET;
    char get[100];
    memset(&get, 0, sizeof(get));

    // Set Server IP Manually//
/*
    printf("enter the server IP:");
    char get[100];
    memset(&get, 0, sizeof(get));
    scanf("%s", &get);
    printf("%s \n",get);
    server.sin_addr.s_addr = inet_addr(get);
*/
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Set Port Number Manually //
/*
    uint16_t por;
    printf("enter the server Port:");
    cin>>por;
    cout<<por<<endl;
    server.sin_port = htons(por);
*/
    server.sin_port = htons(9527);
    
    // Set File Name Manually //
    memset(&get, 0, sizeof(get));
    printf("enter the file name:");
    scanf("%s", &get);
    //printf("%s \n",get);
    
    int tmp = -56;
    tmp = connect(sockfd, (struct sockaddr*) &server, sizeof(server));
    
    if (tmp==0)
        printf("connect success \n");
    else
    {
        printf("%d connect failed \n",tmp);
        return 0;
    }
    
    write(sockfd, get, sizeof(get));
    
    struct stat filestat;
    FILE *fp;
    int numbytes;
    char buf[1000000];
    
    if(lstat(get, &filestat)<0){
        printf("no file \n");
        exit(1);
    }
    
    cout<<"The file size is "<<filestat.st_size<<endl;
    
    fp = fopen(get, "rb");
    
    while(!feof(fp)){
        numbytes = fread(buf, sizeof(char), sizeof(buf), fp);
        printf("fread %d bytes, ", numbytes);
        numbytes = write(sockfd, buf, numbytes);
        printf("Sending %d bytes\n",numbytes);
    }
    
    /*
    char buf[128];
    bzero(buf,128);
    printf("Please key in message:");
    scanf("%s", &buf);
    write(sockfd, buf, strlen(buf));
    */
    close(sockfd);
    
    return 0;
}