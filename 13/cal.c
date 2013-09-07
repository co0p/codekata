/* calender.c */

#include <stdio.h>
#include <stdlib.h>

#define JULIAN    1
#define GREGORIAN 2

/*
 * return the day of the week for particualr date
 * flag JULIAN or GREGORIAN
 * (the divisions are integer divisions that truncate the result)
 * Sun = 0, Mon = 1, etc.
 */
int get_week_day(int day, int month, int year, int mode) {
  int a, m, y;

  a = (14 - month) / 12;
  y = year - a;
  m = month + 12*a - 2;

  if (mode == JULIAN) {
    return (5 + day + y + y/4 + (31*m)/12) % 7;
  }

  return (day + y + y/4 - y/100 + y/400 + (31*m)/12) % 7; // GREGORIAN
}


int main(int argc, char *argv[]) {

    int year, month, date, i;
    int startingDay;     /* of the week: init from user input*/
    int padding[12] = { 2,  1,  4,  4,  6,  5,  5,  3,  0,  2,  1,  1}; /* '-' chars to append to month headling */
    int months[12]  = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    char *names[] = {"January", "February", "March", "April", "May", "June",
                    "July", "August", "September", "October", "November", "December"};

    if (argc > 1) {
        year = atoi(argv[1]);
    }
    else {
        printf("Enter the year of your desired calendar: ");
        scanf("%d", &year);
    }

    if (year <= 0 || year > 65535) {
        fprintf(stderr,"ERROR: invalid year (should be small positive integer)\n");  // or > 1532 ?
        exit(EXIT_FAILURE);
    }

    startingDay = get_week_day(1, 1, year,GREGORIAN);

    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
       months[1] = 29;  // leap year

    for (month = 0; month < 12; ++month) {
        const int daysInMonth = months[month];  /* set # of days */
        int dayOfWeek, date;

        printf("\n  ------------%s------------", names[month]);   // month name
        for (i = 0; i < padding[month]; ++i) {
            printf("-");
        }
        printf("\n");

        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");         // days of week

        for (dayOfWeek = 0; dayOfWeek < startingDay; ++dayOfWeek)
            printf("     ");

        for (date = 1; date <= daysInMonth; ++date) {
            printf("%5d", date);

            if (++dayOfWeek > 6) {
                printf("\n");
                dayOfWeek = 0;
            }
        } // for date

        if (dayOfWeek != 0)
            printf("\n");

        startingDay = dayOfWeek;
    } // for month

    return EXIT_SUCCESS;
}
