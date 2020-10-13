#ifndef timestamps_h
#define timestamps_h

#include "Arduino.h"

class Timestamps {
	private:
		unsigned int getTimestamp(int referenceYear, int year, int month, int day, int hour, int minute, int second, int setTimeZoneOffset);
		int* getDateFromTimestamp(int timestamp, int timeOffset=0, int referenceYear=1970);
	/*
		static int secondsPerHour;
		static int secondsPerDay;
		static int daysPerMonth[12];

		int formattedDate[6];
		*/
		int _timeZoneOffset=0;

		const int secondsPerHour = 60*60;
		const int secondsPerDay = 24 * secondsPerHour;
		int daysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
		int formattedDate[6] = {0,0,0,0,0,0};

	public:
		Timestamps(int setTimeZoneOffset=0);
		unsigned int getTimestampUNIX(int year, int month, int day, int hour, int minute, int second, int setTimeZoneOffset=0);
		unsigned int getTimestampNTP(int year, int month, int day, int hour, int minute, int second, int setTimeZoneOffset=0);
		bool isLeapYear(unsigned int year);

		int getYears(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getMonths(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getDays(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getHours(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getMinutes(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getSeconds(int timestamp, int timeOffset=0, int referenceYear=1970);


	};

#endif
