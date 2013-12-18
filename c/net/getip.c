#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>

/* Given a ifreq structure this function returns its IP address */
void getip(struct ifreq *ifr, char *addr)
{
    struct sockaddr *sa;

    sa = (struct sockaddr *)&(ifr->ifr_addr);
    switch (sa->sa_family)
    {
        case AF_INET6:
            inet_ntop(AF_INET6, (struct in6_addr *)&(((struct sockaddr_in6 *)sa)->sin6_addr), addr, INET6_ADDRSTRLEN);
            break;
        default : 
            strcpy(addr, (const char *)inet_ntoa(((struct sockaddr_in *)sa)->sin_addr));
    }

}

void test()
{
    struct ifreq ifr;
    char netaddr[INET_ADDRSTRLEN];
    int sd;
    
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, "eth0");

    if((ioctl(sd, SIOCGIFADDR, (caddr_t)&ifr, sizeof(struct ifreq))) < 0)
        perror("Error : ");

    getip(&ifr, netaddr);

    printf("%s\n", netaddr);

}

int main()
{

    test();

    return 0;
}
