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
#include <iostream>
using namespace std;

int main(){
    
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    
    server.sin_family= AF_INET;
    server.sin_port = htons(9527);                      // set port number
    
    
    char get[100];
    memset(&get, 0, sizeof(get));
    printf("enter the server IP:");
    scanf("%s", &get);
    //printf("%s \n",get);
    server.sin_addr.s_addr = inet_addr(get);
    
    //server.sin_addr.s_addr = inet_addr("140.112.183.70"); // set server IP
    //server.sin_addr.s_addr = inet_addr("36.228.148.101");
    
    int tmp = -56;
    tmp = connect(sockfd, (struct sockaddr*) &server, sizeof(server));
    
    if (tmp==0)
        printf("connect success \n");
    else
    {
        printf("%d connect failed \n",tmp);
        return 0;
    }
    
    /*
    char buf[128];
    bzero(buf,128);
    printf("Please key in message:");
    scanf("%s", &buf);
    */
    
    int buf[2];
    memset(buf, 0, sizeof(buf));
    
    while(1){
        string ans;
        cout<<"enter your guess:"<<endl;
        cin>>ans;
    
        int A[4];
        for(int i=0;i<4;i++)
            A[i] = ans[i]-'0';
    
        write(sockfd, A, sizeof(A));
        
        recv(sockfd, buf, sizeof(buf), 0);
        
        cout<<"result:";
        cout<<buf[0]<<"A"<<buf[1]<<"B"<<endl;
        if(buf[0]==4){
            cout<<"You Got Ans!\n";
            break;
        }
        memset(buf, 0,sizeof(buf));
    }
    close(sockfd);
    
    return 0;
}