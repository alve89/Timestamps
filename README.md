# Timestamps
A standalone library, mainly for Arduino clients, to generate timestamps (both UNIX and NTP) for given dates/times. 

## Purpose
You might want to use it in combination with the [TimeLib](https://github.com/PaulStoffregen/Time) to generate timestamps of either a date/time when the compiler ran or to generate offline timestamps as backup if your NTP server request fails (may be due to loss of internet connection).

## Examples
You can find simple examples in the [examples](https://github.com/alve89/Timestamps/blob/master/examples/getTimestamps.ino) section.

## Usage
The only thing you need to do is to include this library into your sketch:
1. Download the latest version from [releases](https://github.com/alve89/Timestamps/releases/latest)
2. Extract the archive and move the *Timestamps* folder to your _~/Arduino/libraries/_ directory
3. If your Arduino IDE is already running, restart it
4. Include this library via _Sketch->Include Library->Timestamps_ or simply by adding this row at the begin of your sketch: `#include <Timestamps.h>`
5. You're ready to use it, have fun! Feel free to contact me if something doesn't work or you miss anything.
