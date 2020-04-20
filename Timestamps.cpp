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

int* Timestamps::getDateFromTimestamp(int timestamp, int timeOffset=0, int referenceYear=1970) {
	int y = referenceYear; // this returns the current year. Default is referenceYear, which will be incremented.
	int month = 0; // this returns the current month

	timestamp += timeOffset;

	while(timestamp/(365*secondsPerDay) > 0) {
		timestamp -= 365*secondsPerDay;
		if(isLeapYear(y)) {
				// Year is leap year -> substract one more day
				timestamp -= secondsPerDay;
		}
		y++;
	}
	formattedDate[0] = y;

	for(int m=1; m<=12; m++) {
		timestamp = timestamp - (daysPerMonth[m-1]*secondsPerDay);
		cout << m << endl;
		if(timestamp - (daysPerMonth[m]*secondsPerDay) < 0) {
				month = m+1;
				break;
		}
	}
	formattedDate[1] = month;

	int d = timestamp/secondsPerDay;
	timestamp = timestamp - d*secondsPerDay;
	formattedDate[2] = d;

	int h = timestamp/3600;
	timestamp = timestamp - h*3600;
	formattedDate[3] = h;

	int m = timestamp / 60;
	timestamp = timestamp - m*60;
	formattedDate[4] = m;

	int s = timestamp % 60;
	formattedDate[5] = s;

	return formattedDate;
}

// Returns year of given timestamp
int Timestamps::getYears(int timestamp, int timeOffset=0, int referenceYear=1970) {
	return getDateFromTimestamp(timestamp, timeOffset, referenceYear)[0];
}

// Returns month of given timestamp
int Timestamps::getMonths(int timestamp, int timeOffset=0, int referenceYear=1970) {
	return getDateFromTimestamp(timestamp, timeOffset, referenceYear)[1];
}

// Returns day of given timestamp
int Timestamps::getDays(int timestamp, int timeOffset=0, int referenceYear=1970) {
	return getDateFromTimestamp(timestamp, timeOffset, referenceYear)[2];
}

// Returns hours of given timestamp
int Timestamps::getHours(int timestamp, int timeOffset=0, int referenceYear=1970) {
	return getDateFromTimestamp(timestamp, timeOffset, referenceYear)[3];
}

// Returns minutes of given timestamp
int Timestamps::getMinutes(int timestamp, int timeOffset=0, int referenceYear=1970) {
	return getDateFromTimestamp(timestamp, timeOffset, referenceYear)[4];
}

// Returns seconds of given timestamp
int Timestamps::getSeconds(int timestamp, int timeOffset=0, int referenceYear=1970) {
	return getDateFromTimestamp(timestamp, timeOffset, referenceYear)[5];
}



int Timestamps::secondsPerHour = 60*60;
int Timestamps::secondsPerDay = 24 * secondsPerHour;
int Timestamps::daysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
int formattedDate[6] = {0,0,0,0,0,0};
