#include "time.h"

int minutesSinceMidnight(Time time) {
    // Function returns the number of minutes from 0:00 AM until time.
    return (time.h * 60) + time.m;
}

int minutesUntil(Time earlier, Time later) {
    /*
    Function receive two Time arguments earlier and later 
    and reports how many minutes separate the two moments.
    */
    return minutesSinceMidnight(later) - minutesSinceMidnight(earlier);
}

Time addMinutes(Time time0, int min) {
    // Function create and return a new moment of time that is min minutes after time 0
    int time0_min = minutesSinceMidnight(time0); 
    time0_min += min;
    if (time0_min >= (24 * 60)) { // after 23:59 it goes back to 00:00
        time0_min -= (24 * 60);
    }
    Time new_time = {time0_min / 60, time0_min % 60};
    return new_time;
}

