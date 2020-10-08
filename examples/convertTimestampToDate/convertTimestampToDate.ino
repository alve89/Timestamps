#include <Timestamps.h>

// This example returns a pointer to an array with all date/time elements (array[year, month, day, hour, minute, second])
// int* Timestamps::getDateFromTimestamp(int timestamp, int timeOffset=0, int referenceYear=1970) {
Timestamps timestamps;
int* datetime = timestamps.getDateFromTimestamp(1580393716);
/*
this returns a pointer to an ay with these elements:
{2020, 1, 30, 14, 15, 16}
which is correspondig to the date 30.01.2020 - 14:15:16
when using 1970 as reference date, which is the default value of argument 3.

You can also create a date/time from NTP timestamps by setting argument 3 to 1900
*/

// You can also retrieve the single elements by using the following functions:
// timestmaps.getYears(1580393716); // returns 2020
// timestmaps.getMonths(1580393716); // returns 1
// timestmaps.getDays(1580393716); // returns 30
// timestmaps.getHours(1580393716); // returns 14
// timestmaps.getMinutes(1580393716); // returns 15
// timestmaps.getSeconds(1580393716); // returns 16

