/*
Here's an example of how to generate two timestamps:
1. UNIX-timestamp: Used by most clients like servers etc.
2. NTP-timestamp: Can be retrieved by network-shields and calls to a NTP server
*/

#include <Timestamps.h>

Timestamps ts(3600); // instantiating object of class Timestamp with an time offset of 3.600 seconds for Western Eurpean Time

void setup() {
	Serial.begin(115200);
	while(!Serial) {
		// While serial port is not ready yet, wait a time for it
		delay(100);
	}
}

void loop() {
	Serial.print("UNIX timestamp: ");
	// Get the timestamp for the given date (25. January 2020) and time (14:30:20)
	Serial.println(ts.getTimestampUNIX(2020, 1, 25, 14, 30, 20)); // returns: 1579962620 (remember the given offset of 3600 seconds in line 9)

	Serial.print("UNIX timestamp without offset: ");
	// You can also use a specified time offset, here "0" as last parameter
	Serial.println(ts.getTimestampUNIX(2020, 1, 25, 14, 30, 20, 0)); // returns: 1579959020 (notice the given offset of 0 [last parameter])

	Serial.print("NTP timestamp: ");
	Serial.println(ts.getTimestampNTP(2020, 1, 25, 14, 30, 20)); // returns: 3788951420 (remember the given offset of 3600 seconds in line 9)
}
