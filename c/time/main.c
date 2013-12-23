#include <stdio.h>
#include "time.h"


void test_day()
{
    int year[10] = {2013, 2013, 2013, 2013, 2013, 1988, 1938, 1500, 800, 1970};
    int month[10] = {2, 3, 7, 8, 11, 2, 8, 12, 5, 1};
    int day[10] = {12, 24, 27, 3, 5, 30, 2, 19, 22, 28};

    int i;

    for (i=0; i<10; i++)
    {
        printf("%4.4d-%2.2d-%2.2d:  %3d day.\n", year[i], month[i], day[i], day_of_year(year[i], month[i], day[i]));
    }

}

void test()
{
    test_day();
}

int main()
{
    test();
    return 0;
}
