
//void example()
//{
//    static struct timeval lasttime = { 0, 0 };
//    static struct timeval timediff = { 0, 0 };
//    static long elapsed_msecs;
//    struct timeval thistime;
//
//    /* timestamp and time difference */
//    gettimeofday(&thistime, 0);
//    timersub(&thistime, &lasttime, &timediff);
//    elapsed_msecs = timediff.tv_sec * 1000 + timediff.tv_usec / 1000;
//    lasttime = thistime; //??struct assign like memcpy
//}
//

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/*
 * day_of_year() converts the month and day into the day of the year.
 */
int day_of_year(int year, int month, int day)
{
    int i, leap, yearday;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    yearday = day;

    for (i=1; i<month; i++)
        yearday += daytab[leap][i];

    return yearday;
}

/*
 * month_day() converts the day of the year into the month and day.
 */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    for (i=1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;

}
