#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static inline char *skip_ws(const char *p)
{
    while (isspace(*p)) p++; 
    return (char *)p; 
}
    
int main(void)
{
    FILE *fp;
    char *line = NULL, *p = NULL;
    size_t len = 0;
    ssize_t read;

    int use_agent, reg_frequency, sip_port, sip_vice_port;
    char sip_ip[16], sip_vice_ip[16];

    char *token;
    char *delim = ", ";

    fp = fopen("agent.conf", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    printf("%d %s %s %s:%d [%s %s]\n", i++, __FUNCTION__ , __func__, __FILE__, __LINE__, __DATE__, __TIME__);
    // use_agent, reg_frequency, sip_ip, sip_port, sip_vice_ip, sip_vice_port

    while ((read = getline(&line, &len, fp)) != -1) {
        p = skip_ws(line);
        if (*p == '#')
            continue;

        printf("%s", line);

        token = strtok(p, delim);
        use_agent = atoi(token);

        token = strtok(NULL, delim);
        reg_frequency = atoi(token);

        token = strtok(NULL, delim);
        snprintf(sip_ip, sizeof(sip_ip), "%s", token);
        token = strtok(NULL, delim);
        sip_port = atoi(token);
        
        token = strtok(NULL, delim);
        snprintf(sip_vice_ip, sizeof(sip_vice_ip), "%s", token);
        token = strtok(NULL, delim);
        sip_vice_port = atoi(token);

        printf("%d, %d, %s, %d, %s, %d\n", use_agent, reg_frequency, sip_ip, sip_port, sip_vice_ip, sip_vice_port);

    }

    free(line);
    fclose(fp);
    exit(EXIT_SUCCESS);
}

