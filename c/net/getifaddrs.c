#include <arpa/inet.h>
#include <ifaddrs.h>
#include <stdio.h>

void test()
{
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs(&ifap);

    for (ifa = ifap; ifa; ifa = ifa->ifa_next) 
    {
        if (ifa->ifa_addr->sa_family == AF_INET) 
        {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            printf("%6s: %s\n", ifa->ifa_name, addr);
        }
        else
        {
        }
    }

    freeifaddrs(ifap);

}

int main()
{
    test();
    return 0;
}
