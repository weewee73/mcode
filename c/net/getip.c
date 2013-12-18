#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>


void test()
{
    struct ifreq ifr;
    int sd;
    struct sockaddr_in *addr;
    unsigned char *mac;
    char *address;
    
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, "eth0");

    if((ioctl(sd, SIOCGIFADDR, &ifr)) < 0)
    {
        perror("ioctl SIOCGIFADDR error");
    }
    addr = (struct sockaddr_in *)&(ifr.ifr_addr);
    address = (char *)inet_ntoa(addr->sin_addr);
    printf("inet addr: %s\n", address);


    if (ioctl(sd, SIOCGIFHWADDR, &ifr) == -1)
    {
        perror("ioctl SIOCGIFHWADDR error");
    }
    mac = (unsigned char*)(ifr.ifr_hwaddr.sa_data);
    printf(" mac addr: %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

}

int main()
{

    test();

    return 0;
}
