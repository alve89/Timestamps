#ifndef timestamps_h
#define timestamps_h

#include "Arduino.h"

class Timestamps {
	public:
		Timestamps(int setTimeZoneOffset);
		unsigned int getTimestampUNIX(int year, int month, int day, int hour, int minute, int second, int setTimeZoneOffset);
		unsigned int getTimestampNTP(int year, int month, int day, int hour, int minute, int second, int setTimeZoneOffset);
		bool isLeapYear(unsigned int year);

		int getYears(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getMonths(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getDays(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getHours(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getMinutes(int timestamp, int timeOffset=0, int referenceYear=1970);
		int getSeconds(int timestamp, int timeOffset=0, int referenceYear=1970);

	private:
		unsigned int getTimestamp(int referenceYear, int year, int month, int day, int hour, int minute, int second, int setTimeZoneOffset);
		int* getDateFromTimestamp(int timestamp, int timeOffset=0, int referenceYear=1970);
		static int secondsPerHour;
		static int secondsPerDay;
		static int daysPerMonth[12];
		int _timeZoneOffset;
	};

#endif
