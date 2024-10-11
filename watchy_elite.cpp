#include "watchy_elite.h"


void WatchyElite::drawWatchFace(){
  display.fillScreen(GxEPD_BLACK);
  display.setTextWrap(false);

  sun.setPosition(settings.lat.toFloat(), settings.lon.toFloat(), settings.gmtOffset / 3600);

  drawOuterRing(97);
  drawDayRing(85);
  drawMinuteRing(65);
  drawHourRing(45);

  //the ship
  display.fillTriangle(100, 96, 105, 104, 95, 104, GxEPD_WHITE);

  //forward view limiter
  display.drawLine(
    100,
    100,
    100 + 98 * sin(25 * DEG2RAD),
    100 + 44 * -cos(25 * DEG2RAD),
    GxEPD_WHITE
    );

  //forward view limiter
  display.drawLine(
    100,
    100,
    100 + 98 * sin(-25 * DEG2RAD),
    100 + 44 * -cos(-25 * DEG2RAD),
    GxEPD_WHITE
    );

  drawBattery();
  drawTime();
  drawMinute(65,.45);
  drawHour(45,.45);
  drawMoon(85,.45);
  }


void WatchyElite::drawBattery() {
  display.setTextColor(GxEPD_WHITE);
  display.setCursor(2, 185);
  display.setFont(&FreeSansBold9pt7b);
  display.printf("%04dmV", analogReadMilliVolts(BATT_ADC_PIN) * 2);
  }


void WatchyElite::drawTime() {
  display.setTextColor(GxEPD_WHITE);
  display.setFont(&FreeSansBold9pt7b);
  
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "%d %s %04d %02d:%02d", currentTime.Day, monthStr(currentTime.Month), 3256 + currentTime.Year, currentTime.Hour, currentTime.Minute);

  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(F(buffer), 0, 0, &x1, &y1, &w, &h);

  int16_t xPos = (200 - w) / 2;
  display.setCursor(xPos, 18);

  display.drawLine(2, 2, 196, 2, GxEPD_WHITE);

  display.drawLine(2, 22, 196, 22, GxEPD_WHITE);
  display.print(buffer);
  }

void WatchyElite::drawMinute(int16_t ring_width, float aspect) {
  float minuteAngle = 360.0 * (currentTime.Minute / 60.0);

  display.fillRect(
    100 + ring_width * sin(minuteAngle * DEG2RAD) - 2,
    100 + ring_width * -cos(minuteAngle * DEG2RAD) - 2,
    5,
    5,
    GxEPD_WHITE
    );

  display.drawLine(
    100 + ring_width * sin(minuteAngle * DEG2RAD),
    100 + ring_width * -cos(minuteAngle * DEG2RAD),
    100 + ring_width * sin(minuteAngle * DEG2RAD),
    100 + ring_width * aspect * -cos(minuteAngle * DEG2RAD),
    GxEPD_WHITE
    );
  }

void WatchyElite::drawHour(int16_t ring_width, float aspect) {
  float hourAngle = 360.0 * (currentTime.Hour / 24.0);

  display.fillRect(
    100 + ring_width * sin(hourAngle * DEG2RAD) - 3,
    100 + ring_width * -cos(hourAngle * DEG2RAD) - 3,
    7,
    7,
    GxEPD_WHITE
    );

  display.drawLine(
    100 + ring_width * sin(hourAngle * DEG2RAD),
    100 + ring_width * -cos(hourAngle * DEG2RAD),
    100 + ring_width * sin(hourAngle * DEG2RAD),
    100 + ring_width * aspect * -cos(hourAngle * DEG2RAD),
    GxEPD_WHITE
    );
  }


void WatchyElite::drawMoon(int16_t ring_width, float aspect){

  float dayAngle = 360.0 / DaysPerMonth(currentTime.Year, currentTime.Month) * currentTime.Day;

  
  
  display.setFont(&MoonPhases20pt7b);
  long long unix_time = makeTime(currentTime) + settings.gmtOffset;
  int moonphase = sun.moonPhase(unix_time);


  display.fillCircle(
    100 + ring_width * sin(dayAngle * DEG2RAD),
    100 + ring_width * -cos(dayAngle * DEG2RAD),
    14, 
    GxEPD_BLACK
    );

  display.setCursor(
    100 + ring_width * sin(dayAngle * DEG2RAD)  - 14,
    100 + ring_width * -cos(dayAngle * DEG2RAD) + 14
    );
  display.print((char)(moonphase+0x50));


  display.drawLine(
    100 + ring_width * sin(dayAngle * DEG2RAD),
    100 + ring_width * -cos(dayAngle * DEG2RAD),
    100 + ring_width * sin(dayAngle * DEG2RAD),
    100 + ring_width * aspect * -cos(dayAngle * DEG2RAD),
    GxEPD_WHITE
    );
  }

int16_t WatchyElite::DaysPerMonth(int16_t year, int16_t month) {
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



void WatchyElite::drawOuterRing(int16_t ring_width){
  drawRing(98,.45, 360);
  }

void WatchyElite::drawDayRing(int16_t ring_width){
  drawRing(85,.45, DaysPerMonth(currentTime.Year, currentTime.Month) );
  }

void WatchyElite::drawMinuteRing(int16_t ring_width){
  drawRing(65,.45, 60);
  }

void WatchyElite::drawHourRing(int16_t ring_width){
  drawRing(45,.45, 24);
  }

void WatchyElite::drawRing(int16_t ring_width, float aspect, int16_t mark_count){
  for(float i = 0; i < 360; i += 360.0 / mark_count) {
    display.drawPixel(
      100 + ring_width * sin(i * DEG2RAD),
      100 + ring_width * aspect * -cos(i * DEG2RAD),
      GxEPD_WHITE
      );
    }
  }