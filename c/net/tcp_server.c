#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define DEFAULT_PORT 8000
#define MAXPENDING 10 /* Max connection requests */
#define BUFFSIZE 1024

void Die(char *mess){ perror(mess); exit(1); }


#include <fcntl.h>
void setSockNonBlock(int sock) {
    int flags;

    flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0) {
        perror("fcntl(F_GETFL) failed");
        exit(EXIT_FAILURE);
    }

    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("fcntl(F_SETFL) failed");
        exit(EXIT_FAILURE);
    }
}
#include <sys/time.h>
void HandleClient2(int sock){
    char buffer[BUFFSIZE];
    int received=-1;
    int res;

    fd_set readfds;
    struct timeval timeout={0, 0};

    setSockNonBlock(sock);

    /* 发送字节，并在循环中检查是否有更多进来的数据 */
    while (1) {

        //每次循环都要清空集合，否则不能检测描述符变化
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);

        res = select(sock + 1, &readfds, NULL, NULL, &timeout);
        if (res == -1) {
            perror("select failed");
            exit(EXIT_FAILURE);
        }
        else if (res == 0) {
            //fprintf(stderr, "no socket ready for read within %d secs\n", SELECT_TIMEOUT);
            continue;
        }

        if (!FD_ISSET(sock, &readfds)) {
            continue;
        }

        memset(buffer, 0, sizeof(buffer));

        /* 检查更多进来的数据 */
        if((received=recv(sock, buffer, BUFFSIZE, 0))<0){
            Die("Failed to receive additional bytes from client");
        }

        if (received == 0) {
            close(sock);
            fprintf(stdout, "Client disconnected.\n\n");
            return ;
        }

        /* 把接收的数据发送回去 */
        if(send(sock, buffer, received, 0)!=received){
            Die("Failed to send bytes to client");
        }
    }
}

void HandleClient(int sock){
    char buffer[BUFFSIZE];
    int received=-1;

    /* 接收消息 */
    if((received=recv(sock, buffer, BUFFSIZE, 0))<0){
        Die("Failed to receive initial bytes from client");
    }

    /* 发送字节，并在循环中检查是否有更多进来的数据 */
    while(received>0){

        /* 把接收的数据发送回去 */
        if(send(sock, buffer, received, 0)!=received){
            Die("Failed to send bytes to client");
        }

        /* 检查更多进来的数据 */
        if((received=recv(sock, buffer, BUFFSIZE, 0))<0){
            Die("Failed to receive additional bytes from client");
        }
    }

    close(sock);
    fprintf(stdout, "Client disconnected.\n\n");
}

int main(int argc, char** argv)  
{  
    int    socket_fd, connect_fd;
    struct sockaddr_in     servaddr, clientaddr;

    //创建TCP Socket
    if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
        Die("Failed to create socket");
    }  

    //in case of 'address already in use' error message
    int yes = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    //构造地址族结构
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   //IP地址设置成INADDR_ANY，让系统自动获取本机的IP地址
    servaddr.sin_port = htons(DEFAULT_PORT);        //设置的端口为DEFAULT_PORT

    //将地址族绑定到套接字上
    if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        Die("Failed to bind the server socket");
    }  

    //监听是否有客户端连接
    if(listen(socket_fd, MAXPENDING) == -1){
        Die("Failed to listen on server socket");
    }  

    printf("======waiting for client's request======\n");

    /* 一直运行，直到取消 */
    while(1){
        //阻塞直到有客户端连接，不然多浪费CPU资源
        unsigned int clientlen=sizeof(clientaddr);

        if((connect_fd = accept(socket_fd, (struct sockaddr*)&clientaddr, &clientlen)) == -1){
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }

        fprintf(stdout, "Client connected: %s:%d\n", inet_ntoa(clientaddr.sin_addr), clientaddr.sin_port);

        //处理客户连接
        HandleClient(connect_fd);
    } 
}
