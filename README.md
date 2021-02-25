# ESP.DS3231_RTC
Wrapper for the DS3231 RTC for ESP8266 and ESP32 with Arduino Environment. Uses the Adafruit RTClib.\
Allows to pass callback function for SQWV Pin interrupts and provides convenient timeStr method.

Requirements:
- Adafruit [RTClib](https://adafruit.github.io/RTClib/html/index.html)

Supports:
- [multiLogger](http://github.com/voelkerb/ESP.multiLogger)

```C++
#include "DS3231_RTC.h"


// Constructor with or without interrupt pin
#define RTC_INT 26
Rtc rtc(RTC_INT);

int i = 0;
int frequency = 1024;

void setup() {
  Serial.begin(9600);
  // Get back if init was successful
  bool success = rtc.init();
  if (success) Serial.println("RTC successfully initialized")
  ...
  // Set RTC time to a time, e.g. compile time (remove after setting ONCE)
  rtc.setTime(DateTime(__DATE__, __TIME__));
  // Enable a pin interrupt Frequency in Hz. Possibilities: 1Hz, 1024Hz, 4096Hz, 8192Hz
  rtc.enableInterrupt(frequency, &rtcInt);
}

void loop() {
  ...
  if (flag) {
    Serial.println("Another damn second passed...");
    // Get current time
    DateTime now = rtc.update();
    // print current time using rtc.timeStr(); or optionally 
    rtc.timeStr(now);
    flag = false;
  }
}

// Interrupt handler
void rtcInt() {
  if (i%frequency == 0) {
    Serial.println(rtc.timeStr());
    flag = true;
  }
  i++;
}
```


Output 

```bash
RTC successfully initialized
02/25/2021 15:53:48
Another damn second passed...
02/25/2021 15:53:48
02/25/2021 15:53:49
Another damn second passed...
02/25/2021 15:53:49
...

```
