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


int main(void) {

    int year, month, date;
    int startingDay;     /* of the week: init from user input*/
    char *names[] = {"January", "February", "March", "April", "May", "June",
                    "July", "August", "September", "October", "November", "December"};

    printf("Enter the year of your desired calendar: ");
    scanf("%d", &year);

    // could check whether input is valid here

    startingDay = get_week_day(1, 1, year,GREGORIAN);

    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
       months[1] = 29;

    for (month = 0; month < 12; ++month) {
        const int daysInMonth = months[month];  /* set # of days */
        int dayOfWeek, date;

        printf("\n  ------------%s-------------\n", names[month]);   // month name
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
