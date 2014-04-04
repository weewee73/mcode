// C3-100 ZK
#include <arpa/inet.h>
#include <strings.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE     4096    /* max text line length */

#define DEFAULT_IP	"192.168.2.251"
#define DEFAULT_PORT	4370

unsigned char door_open[] = { 0xaa, 0x01, 0x05, 0x05, 0x00, 0x01, 0x01, 0x01, 0x0f, 0x00, 0xf0, 0xa3, 0x55 };
unsigned char door_close[] = { 0xaa, 0x01, 0x05, 0x05, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0xf5, 0x53, 0x55 };
unsigned char response_open_close[] = { 0xaa, 0x01, 0xc8, 0x00, 0x00, 0x80, 0x02, 0x55 };

unsigned char door_query[] = { 0xaa, 0x01, 0x0b, 0x00, 0x00, 0x70, 0x3e, 0x55 };
unsigned char response_query[] = { 0xaa, 0x01, 0xc8, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xc8, 0x00, 0xff,  0x00, 0xb2, 0x9c, 0x3c, 0x1b, 0xb1, 0x07, 0x55 }; 
unsigned char response_query_open[] = { 0xaa, 0x01, 0xc8, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x01, 0x08, 0x02, 0x66, 0x09, 0x3b, 0x1b, 0x1f, 0x6b, 0x55 }; 
unsigned char response_query_close[] = { 0xaa, 0x01, 0xc8, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x01, 0x09, 0x02, 0xe7, 0x09, 0x3b, 0x1b, 0x36, 0x86, 0x55 };


void hex_print(const unsigned char *buf, int size)
{
    int i;

    for (i=0; i<size-1; i++)
    {
        printf(" 0x%02x,", buf[i]);
    }
    printf(" 0x%02x\n", buf[i]);
}

int main(int argc, char **argv)
{
	int					sockfd, n;
	unsigned char		recvline[MAXLINE + 1];
    unsigned char       *p_send = door_query;
    unsigned char       *p_res = response_query;
    int                 nsend = sizeof(door_query);
	struct sockaddr_in	servaddr;

    char *ip = DEFAULT_IP;
	int port = DEFAULT_PORT;

	if (argc != 4)
    {
		printf("usage: %s [open|close|query] <server's address> <server's port>\n...using default query %s:%d\n", argv[0], ip, port);
    }
    else
    {
        port = atoi(argv[3]);
        ip = argv[2];

        if (0 == strcmp("open", argv[1]))
        {
            p_send = door_open;
            nsend = sizeof(door_open);
        }
        else if (0 == strcmp("close", argv[1]))
        {
            p_send = door_close;
            nsend = sizeof(door_close);
        }
        else
        {
            p_send = door_query;
            nsend = sizeof(door_query);
        }
    }


	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
		perror("socket error");
        exit(-1);
    }

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(port);
	if (inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0)
    {
		perror("inet_pton error");
        exit(-1);
    }

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
		perror("connect error");
        exit(-1);
    }


    if (nsend != write(sockfd, p_send, nsend))
    {
        perror("write error");
        exit(-1);
    }
    printf("send:");
    hex_print(p_send, nsend);

    if (0 > (n = read(sockfd, recvline, MAXLINE)))
    {
		perror("read error");
        exit(-1);
    }
    printf("recv:");
    hex_print(recvline, n);



    return 0;
}
