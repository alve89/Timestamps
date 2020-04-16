#ifndef timestamps_h
#define timestamps_h

#include "Arduino.h"

class Timestamps {
	public:
		Timestamps(int setTimeZoneOffset);
		unsigned int getTimestampUNIX(int year, int month, int day, int hour, int minute, int second, int setTimeZoneOffset);
		unsigned int getTimestampNTP(int year, int month, int day, int hour, int minute, int second, int setTimeZoneOffset);
		bool isLeapYear(unsigned int year);
	private:
		unsigned int getTimestamp(int referenceYear, int year, int month, int day, int hour, int minute, int second, int setTimeZoneOffset);
		static int secondsPerHour;
		static int secondsPerDay;
		static int daysPerMonth[12];
		int _timeZoneOffset;
	};

#endif
