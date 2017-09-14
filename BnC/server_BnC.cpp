#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<strings.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<iostream>
#include <time.h>
using namespace std;

int main(){
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in dest;
    bzero(&dest, sizeof(dest));
    
    dest.sin_family = AF_INET;
    dest.sin_port = htons(9527);        //set port number
    dest.sin_addr.s_addr = htonl(INADDR_ANY);
    
    bind(sockfd, (struct sockaddr*)&dest, sizeof(dest));
    
    listen(sockfd, 5);
    
    srand(time(NULL));
    int a[10]={0,1,2,3,4,5,6,7,8,9};
    int num[4];
    int tmp;
    
    for(int i=0;i<4;i++)
    {
        tmp = rand()%(10-i);
        num[i] = a[tmp];
        
        int swap;
        swap = a[9-i];
        a[9-i] = a[tmp];
        a[tmp] = swap;
    }
    cout<<"Ans:";
    for(int i=0;i<4;i++)
        cout<<num[i];
    cout<<endl;
    
    printf("waiting\n");
    
    int buf[4];
    memset(buf, 0, sizeof(buf));
    
    int client_fd;
    struct sockaddr_in c_addr;
    
    while(1){
        
        client_fd = accept(sockfd, (struct sockaddr*) NULL, NULL);
        
        while(client_fd >= 0){
            recv(client_fd, buf, sizeof(buf), 0);
            cout<<"client guess:";
            for(int i=0;i<4;i++)
                cout<<buf[i];
            cout<<endl;
            
            int aa[2];
            aa[0]=0;
            aa[1]=0;
            
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    if(buf[i]==num[j]){
                        if(i==j)
                            aa[0]=aa[0]+1;
                        else
                            aa[1]=aa[1]+1;
                    }
                }
            }
            cout<<aa[0]<<"A"<<aa[1]<<"B"<<endl;
            write(client_fd, aa, sizeof(aa));
            
            if(aa[0]==4){
                close(client_fd);
                break;
            }
            memset(buf, 0, sizeof(buf));
            
        }
    }
    close(sockfd);
    return 0;
}