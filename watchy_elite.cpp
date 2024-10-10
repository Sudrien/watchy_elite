#include "watchy_elite.h"


void WatchyElite::drawWatchFace(){
  display.fillScreen(GxEPD_BLACK);
  display.setTextWrap(false);

  sun.setPosition(settings.lat.toFloat(), settings.lon.toFloat(), settings.gmtOffset / 3600);

  // outer (solid)
  for(int16_t i = 0; i < 360; i += 1 ) {
    display.drawPixel(
      100 + 98 * sin(i * DEG2RAD),
      100 + 44 * -cos(i * DEG2RAD),
      GxEPD_WHITE
      );
    }

  //inner (dotted)
  for(int16_t i = 0; i < 360; i += 3 ) {
    display.drawPixel(
      100 + 94 * sin(i * DEG2RAD),
      100 + 40 * -cos(i * DEG2RAD),
      GxEPD_WHITE
      );
    }


  for(int16_t i = 0; i < 360; i += 5 ) {
    display.drawPixel(
      100 + 80 * sin(i * DEG2RAD),
      100 + 33 * -cos(i * DEG2RAD),
      GxEPD_WHITE
      );
    }


  for(int16_t i = 0; i < 360; i += 15 ) {
    display.drawPixel(
      100 + 60 * sin(i * DEG2RAD),
      100 + 24 * -cos(i * DEG2RAD),
      GxEPD_WHITE
      );
    }
  display.fillTriangle(100, 96, 105, 104, 95, 104, GxEPD_WHITE);

  display.drawLine(
    100,
    100,
    100 + 98 * sin(25 * DEG2RAD),
    100 + 44 * -cos(25 * DEG2RAD),
    GxEPD_WHITE
    );

  display.drawLine(
    100,
    100,
    100 + 98 * sin(-25 * DEG2RAD),
    100 + 44 * -cos(-25 * DEG2RAD),
    GxEPD_WHITE
    );

  drawBattery();
  drawTime();
  drawMinute();
  drawHour();
  drawMoon();
  }


void WatchyElite::drawBattery() {
  display.setTextColor(GxEPD_WHITE);
  display.setCursor(2, 185);
  display.setFont(&FreeSansBold9pt7b);
  display.print(analogReadMilliVolts(BATT_ADC_PIN) * 2);
  display.print("mV");
  }


void WatchyElite::drawTime() {
  display.setTextColor(GxEPD_WHITE);
  display.setCursor(155, 191);
  display.setFont(&FreeSansBold9pt7b);
  
  if(currentTime.Hour < 10){
    display.print('0');
    }
  display.print(currentTime.Hour);
  if(currentTime.Minute < 10){
    display.print('0');
    }
  display.print(currentTime.Minute);
  }

void WatchyElite::drawMinute() {
  float minuteAngle = 360.0 * (currentTime.Minute / 60.0);

  display.fillRect(
    100 + 80 * sin(minuteAngle * DEG2RAD) - 2,
    100 + 80 * -cos(minuteAngle * DEG2RAD) - 2,
    5,
    5,
    GxEPD_WHITE
    );

  display.drawLine(
    100 + 80 * sin(minuteAngle * DEG2RAD),
    100 + 80 * -cos(minuteAngle * DEG2RAD),
    100 + 80 * sin(minuteAngle * DEG2RAD),
    100 + 33 * -cos(minuteAngle * DEG2RAD),
    GxEPD_WHITE
    );
  }

void WatchyElite::drawHour() {
  float hourAngle = 360.0 * (currentTime.Hour / 24.0);

  display.fillRect(
    100 + 60 * sin(hourAngle * DEG2RAD) - 3,
    100 + 60 * -cos(hourAngle * DEG2RAD) - 3,
    7,
    7,
    GxEPD_WHITE
    );

  display.drawLine(
    100 + 60 * sin(hourAngle * DEG2RAD),
    100 + 60 * -cos(hourAngle * DEG2RAD),
    100 + 60 * sin(hourAngle * DEG2RAD),
    100 + 24 * -cos(hourAngle * DEG2RAD),
    GxEPD_WHITE
    );
  }


void WatchyElite::drawMoon(){

  float dayAngle = 360.0 / DaysPerMonth(currentTime.Year, currentTime.Month) * currentTime.Day;

  
  
  display.setFont(&MoonPhases20pt7b);
  long long unix_time = makeTime(currentTime) + settings.gmtOffset;
  int moonphase = sun.moonPhase(unix_time);

 display.setCursor(
    100 + 90 * sin(dayAngle * DEG2RAD)  - 10,
    100 + 90 * -cos(dayAngle * DEG2RAD) - 10
    );
  display.print((char)(moonphase+0x50));


  display.drawLine(
    100 + 90 * sin(dayAngle * DEG2RAD),
    100 + 90 * -cos(dayAngle * DEG2RAD),
    100 + 90 * sin(dayAngle * DEG2RAD),
    100 + 40 * -cos(dayAngle * DEG2RAD),
    GxEPD_WHITE
    );
  }

unsigned int WatchyElite::DaysPerMonth(unsigned int year, unsigned int month) {
  if (month == 2) {
    if (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0)) {
      return 28;
      }
    else {
      return 29;
      }
    }
  else if (month == 4 || month == 6 || month == 9 || month == 11) {
    return 30;
    }
  else {
    return 31;
    }
  }