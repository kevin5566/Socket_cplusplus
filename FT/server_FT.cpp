#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in dest;
    bzero(&dest, sizeof(dest));
    
    dest.sin_family = AF_INET;
    dest.sin_port = htons(9527);        //set port number
    dest.sin_addr.s_addr = htonl(INADDR_ANY);
    
    bind(sockfd, (struct sockaddr*)&dest, sizeof(dest));
    
    listen(sockfd, 5);
    
    printf("waiting\n");
    
    //Connect
    int client_fd;
    struct sockaddr_in c_addr;
    
    client_fd = accept(sockfd, (struct sockaddr*) NULL, NULL);
    
    // Name Processing //
    char buf[128];
    memset(&buf, 0, sizeof(buf));
    recv(client_fd, buf, sizeof(buf), 0);
    char newname1[128];
    char newname2[128];
    
    int i;
    for(i=0; i<sizeof(newname1); i++){
        if(buf[i] != '.')
            newname1[i]=buf[i];
        else{
            strcat(newname1,"_from_client");
            break;
        }
            
    }
    int k;
    for(int j=i, k=0;j<sizeof(newname1); k++,j++){
        if(buf[i] != '\0')
            newname2[k]=buf[j];
        else
            break;
    }
    strcat(newname1,newname2);
    
    printf("the file name is %s\n",newname1);
    
    FILE *fp;
    int numbytes;
    if ( (fp = fopen(newname1, "wb")) == NULL){
        exit(1);
    }
    
    
    //Receive file from client
    char buffer[1000000];
    while(1){
        numbytes = read(client_fd, buffer, sizeof(buffer));
        if(numbytes == 0){
            break;
        }
        printf("read %d bytes, ", numbytes);
        numbytes = fwrite(buffer, sizeof(char), numbytes, fp);
        printf("fwrite %d bytes\n", numbytes);
    }
    fclose(fp);
    
    close(client_fd);
    close(sockfd);
    
    return 0;
    
}