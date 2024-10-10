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
        void drawMinute();
        void drawHour();
        void drawMoon();
        unsigned int DaysPerMonth(unsigned int, unsigned int);
};

#endif