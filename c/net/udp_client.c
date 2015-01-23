#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 4096
void Die(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in echoserver;
    struct sockaddr_in echoclient;
    char buffer[BUFFSIZE];
    int echolen;
    unsigned int clientlen;
    int received=0;

    if(argc!=4){
        fprintf(stderr, "USAGE: %s <server_ip> <port> <word>\n", argv[0]);
        exit(1);
    }

    /* 创建UDP socket */
    if((sock=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))<0){
        Die("Failed to create socket");
    }

    /* 构造地址族 */
    memset(&echoserver, 0, sizeof(echoserver));       /* Clear struct */
    echoserver.sin_family=AF_INET;                    /* Internet/IP */
    echoserver.sin_addr.s_addr=inet_addr(argv[1]);    /* IP address */
    echoserver.sin_port=htons(atoi(argv[2]));         /* server port */

    /* 向服务器发送消息 */
    echolen=strlen(argv[3]);
    if(sendto(sock, argv[3], echolen, 0, (struct sockaddr *) &echoserver, sizeof(echoserver)) != echolen){
        Die("Mismatch in number of sent bytes");
    }

    /* 从服务器接收消息 */
    fprintf(stdout, "Received: ");
    clientlen=sizeof(echoclient);
    if((received=recvfrom(sock, buffer, BUFFSIZE, 0, (struct sockaddr *)&echoclient, &clientlen)) != echolen){
        Die("Received a packet from an unexpected server");
    }

    /* 检查接收是否来自正确的服务器 */
    if(echoserver.sin_addr.s_addr!=echoclient.sin_addr.s_addr){
        Die("Received a packet from an unexpected server");
    }
    buffer[received]='\0';  /* Assure null-terminated string */
    fprintf(stdout, "%s\n", buffer);

    /* 关闭套接字 */
    close(sock);

    exit(0);
}

