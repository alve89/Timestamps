/*
  Timestamps.cpp - Library for getting both UNIX and NTP timestamps.
  Created by Stefan Herzog, April 16 2020.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Timestamps.h"

Timestamps::Timestamps(int timeZoneOffset=0) {
	_timeZoneOffset = timeZoneOffset;
}

bool Timestamps::isLeapYear(unsigned int year) {
if (year % 4 == 0) {
		if (year % 100 == 0) {
				if (year % 400 == 0) {
						return true;
				}
				else {
						return false;
				}
		}
		else {
				return true;
		}
}
else {
		return false;
}
}

unsigned int Timestamps::getTimestamp(int referenceYear, int year, int month, int day, int hour, int minute, int second, int timeZoneOffset=0) {
	unsigned int timestamp=0;
	// Either use the time zone offset value from instantiating or the given paramter
	/*
		1. _timeZoneOffset is set AND timeZoneOffset is set -> use timeZoneOffset
		2. _timeZoneOffset is set AND timeZoneOffset is NOT set -> use _timeZoneOffset
		3. _timeZoneOffset is NOT set AND timeZoneOffset is set -> use timeZoneOffset
		4. _timeZoneOffset is NOT set AND timeZoneOffset is NOT set -> use timeZoneOffset
	*/
	if(_timeZoneOffset != 0 && timeZoneOffset != 0) {
		timeZoneOffset = timeZoneOffset;
	}
	else if(_timeZoneOffset != 0 && timeZoneOffset == 0) {
		timeZoneOffset = _timeZoneOffset;
	}
	else if(_timeZoneOffset == 0 && timeZoneOffset != 0) {
		timeZoneOffset = _timeZoneOffset;
	}
	else if(_timeZoneOffset == 0 && timeZoneOffset == 0) {
		timeZoneOffset = timeZoneOffset;
	}
	else {
		// ERROR
	}

	timestamp += timeZoneOffset;

	day <= 0 ? day=0 : day=day-1;
	hour <= 0 ? hour=0 : hour=hour-1;

	for(int y=referenceYear; y<year; y++) {
			timestamp += 365*secondsPerDay;

			if(isLeapYear(y)) {
					// Year is leap year -> add one day to timestamp
					timestamp += secondsPerDay;
			}
	}

	for(int m=1; m<=month; m++) {
		if(month == 1) {
			// we're still in January
			timestamp += day * secondsPerDay; // time until yesterday evening / tonight 0:00
			timestamp += hour * secondsPerHour;
			timestamp += minute*60;
			timestamp += second;
		}
		if(month > 1) {
			timestamp += daysPerMonth[m-1] * secondsPerDay; // last month

			timestamp += day * secondsPerDay; // time until yesterday evening / tonight 0:00
			timestamp += hour * secondsPerHour;
			timestamp += minute*60;
			timestamp += second;

			if(isLeapYear(year) == 0 && month == 3) {
					// current year is leap year, so 29.02. exists
					// Since we're in March now, add the 29.02. to the timestamp
					timestamp += secondsPerDay; // 29.02.
			}
		}
	}
	return timestamp;
}

unsigned int Timestamps::getTimestampUNIX(int year, int month, int day, int hour, int minute, int second, int timeZoneOffset=0) {
return getTimestamp(1970, year, month, day, hour, minute, second, timeZoneOffset);
}

unsigned int Timestamps::getTimestampNTP(int year, int month, int day, int hour, int minute, int second, int timeZoneOffset=0) {
return getTimestamp(1900, year, month, day, hour, minute, second, timeZoneOffset);
}

int Timestamps::secondsPerHour = 60*60;
int Timestamps::secondsPerDay = 24 * secondsPerHour;
int Timestamps::daysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
