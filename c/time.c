static inline char * skip_ws(const char *p)
{
    while (isspace(*p)) 
        p++;

    return (char *)p;
}
    
static inline char * skip_token(const char *p)
{
    while (isspace(*p)) 
        p++;
    while (*p && !isspace(*p)) 
        p++;

    return (char *)p;
}

{
    static struct timeval lasttime = { 0, 0 };
    static struct timeval timediff = { 0, 0 };
    static long elapsed_msecs;
    struct timeval thistime;

    /* timestamp and time difference */
    gettimeofday(&thistime, 0);
    timersub(&thistime, &lasttime, &timediff);
    elapsed_msecs = timediff.tv_sec * 1000 + timediff.tv_usec / 1000;
    lasttime = thistime; //??struct assign like memcpy
}

{
    char buffer[4096+1];
    double load_avg[3];
    char *p;

    //0.00 0.00 0.00 1/108 4146
    load_avg[0] = strtod(buffer, &p);
    load_avg[1] = strtod(p, &p);
    load_avg[2] = strtod(p, &p);
    p = skip_token(p);			/* skip running/tasks */
    p = skip_ws(p);
}
