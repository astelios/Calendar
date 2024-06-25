#include <time.h>
#include <stdio.h>
#include <math.h>

#define RESET "\x1B[0m"
#define BLACK_TEXT "\x1B[30m"
#define WHITE_BACKGROUND "\x1B[47m"
#define BOX_WIDTH 4 // should be 4 and higher 

int get_days_in_month(struct tm *date) {
    int days;

    switch (date->tm_mon)
    {
    case 0:
    case 2:
    case 4:
    case 6:
    case 7:
    case 9:
    case 11:
        days = 31;
        break;
    
    case 3:
    case 5:
    case 8:
    case 10:
        days = 30;
        break;
    case 1:
        // Leap year
        if((date->tm_year + 1900) % 4 == 0 && ((date->tm_year + 1900) % 100 != 0 || (date->tm_year + 1900) % 400 == 0)) 
            days = 29;
        else
            days = 28;
        break;
    }
    return days;
}

int weekday_of_first_of_month(struct tm date) {
    date.tm_mday = 1;
    mktime(&date);

    return date.tm_wday;
}

void print_month(int m) {
    switch (m)
    {
    case 0:
        printf("January");
        break;
    case 1:
        printf("February");
        break;
    case 2:
        printf("March");
        break;
    case 3:
        printf("April");
        break;
    case 4:
        printf("May");
        break;
    case 5:
        printf("June");
        break;
    case 6:
        printf("July");
        break;
    case 7:
        printf("August");
        break;
    case 8:
        printf("September");
        break;
    case 9:
        printf("October");
        break;
    case 10:
        printf("November");
        break;
    case 11:
        printf("December");
        break;

    
    default:
        break;
    }
}

char *weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int main() {
    time_t raw_time;
    struct tm *curr_date;
    int days;
    int i, j;
    int first_of_month;

    // Get time in ticks
    time(&raw_time);

    // Get time in date
    curr_date = localtime(&raw_time);

    days = get_days_in_month(curr_date);

    printf("\n%*c" BLACK_TEXT WHITE_BACKGROUND, BOX_WIDTH*2, ' ');
    print_month(curr_date->tm_mon);
    printf(" - %d" RESET "\n\n", 1900 + curr_date->tm_year);

    // print names
    for(i=0; i<7; i++) {
        printf("%*s", BOX_WIDTH, weekdays[i]);
    }
    putchar('\n');

    first_of_month = weekday_of_first_of_month(*curr_date);
    // for spaces before first day
    for(i=0; i<first_of_month; i++) {
        printf("%*c", BOX_WIDTH, ' ');
    }
    for(j=0; j<days; j++, i++) {
        if(i == 7) {
            i = 0;
            putchar('\n');
        }
        if(j == curr_date->tm_mday - 1)
            printf(BLACK_TEXT WHITE_BACKGROUND "%*d" RESET, BOX_WIDTH, j+1);
        else
            printf("%*d", BOX_WIDTH, j+1);
    }

    putchar('\n');
    putchar('\n');

    return 0;
}