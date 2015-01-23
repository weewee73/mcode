#include<stdio.h>
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  

#define BUFFSIZE 1024
void Die(char *mess) { perror(mess); exit(1); }  

int main(int argc, char** argv)
{  
    int    sockfd, rec_len;
    char   sendline[BUFFSIZE];
    char   buf[BUFFSIZE];
    struct sockaddr_in    servaddr;

    if( argc != 2){
        printf("usage: ./client <ipaddress>\n");
        exit(1);
    }

    //创建socket
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        Die("Failed to create socket");
    }

    //构造服务器地址族
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",argv[1]);
        exit(1);
    }


    //连接服务器
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        Die("Failed to connect with server");
    }  

    printf("send msg to server: \n");  
    fgets(sendline, BUFFSIZE, stdin); 

    //发送数据到服务器 
    if(send(sockfd, sendline, strlen(sendline), 0) < 0) {  
        Die("Send msg error"); 
    }

    //从服务器接收数据
    if((rec_len = recv(sockfd, buf, BUFFSIZE,0)) == -1) {
        Die("Receive msg error");
    }
    buf[rec_len]  = '\0';

    printf("Received: %s",buf);

    //关闭套接字
    close(sockfd);

    exit(0);
}
