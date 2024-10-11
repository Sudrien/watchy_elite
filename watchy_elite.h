#ifndef WATCHY_ELITE
#define WATCHY_ELITE

#include <Watchy.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <sunset.h>
#include "MoonPhases20pt7b.h"

#define DEG2RAD 0.0174532925

class WatchyElite : public Watchy{
    using Watchy::Watchy;
    public:
        void drawWatchFace();
    private:

        SunSet sun;
        void drawBattery();
        void drawTime();
        void drawMinute(int16_t, float);
        void drawHour(int16_t, float);
        void drawMoon(int16_t, float);
        int16_t DaysPerMonth(int16_t, int16_t);


        void drawOuterRing(int16_t);
        void drawDayRing(int16_t);
        void drawMinuteRing(int16_t);
        void drawHourRing(int16_t);
        void drawRing(int16_t, float, int16_t);

};

#endif