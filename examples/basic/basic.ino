/***************************************************
 Example file for using the rtc library.
 
 License: Creative Common V1. 

 Benjamin Voelker, voelkerb@me.com
 Embedded Systems Engineer
 ****************************************************/
#include <DS3231_RTC.h>

void IRAM_ATTR rtcInt();

#if defined(ESP32)
#define RTC_INT 26
#elif defined(ESP8266)
#define RTC_INT D5
#endif


Rtc rtc(RTC_INT);

int i = 0;
bool flag = false;
int frequency = 1024;

void setup() {
  Serial.begin(115200);
  bool success = rtc.init();
  
  if (!success) Serial.println("RTC init failed");
  else Serial.println("RTC successfully initialized");
  // Set RTC time to compile time (remove after setting ONCE)
  rtc.setTime(DateTime(__DATE__, __TIME__));
  // Check current time of RTC
  Serial.println(rtc.timeStr());
  // Frequency in Hz. Possibilities: 1Hz, 1024Hz, 4096Hz, 8192Hz
  rtc.enableInterrupt(frequency, &rtcInt);
}

void loop() {
  if (flag) {
    Serial.println("Another damn second passed...");
    flag = false;
  }
}

// Callback functions for each RTC Sqwave pin interrupt
void IRAM_ATTR rtcInt() {
  if (i%frequency == 0) {
    // make sure no other task is currently using I2C
    Serial.println(rtc.timeStr());
    flag = true;
  }
  i++;
}