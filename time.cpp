#include "time.h"
#include "movie.h"
#include "timeslot.h"

#include <string>
#include <cmath>

int minutesSinceMidnight(Time time) {
    // Function returns the number of minutes from 0:00 AM until time.
    int minutes = (time.h * 60) + time.m;
    if (minutes >= (24 * 60)) {
        while (minutes >= (24 * 60)) {
            minutes -= (24 * 60);
        }
    }
    return minutes;
}

int minutesUntil(Time earlier, Time later) {
    /*
    Function receive two Time arguments earlier and later 
    and reports how many minutes separate the two moments.
    */
    return minutesSinceMidnight(later) - minutesSinceMidnight(earlier);
}

Time addMinutes(Time time0, int min) {
    // Function create and return a new moment of time that is the given minutes after time0
    int time0_min = minutesSinceMidnight(time0); 
    time0_min += min;
    if (time0_min >= (24 * 60)) { // after 23:59 it goes back to 00:00
        time0_min -= (24 * 60);
    } else if (time0_min < 0) {
        time0_min += (24 * 60);
    }
    Time new_time = {time0_min / 60, time0_min % 60};
    return new_time;
}

std::string getTime(Time time) {
    std::string hr = std::to_string(time.h);
    std::string min = "";
    if (time.m < 10) {
        min = "0";
    }

    min += std::to_string(time.m);
    std::string show_time = hr + ":" + min;
    return show_time;
}

std::string getMovie(Movie mv){
    std::string g;
    std::string movie_info;
    std::string duration = std::to_string(mv.duration);
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    movie_info = mv.title + " " + g + " (" + duration + " min)";
    return movie_info;
}

std::string getTimeSlot(TimeSlot ts) {
    std::string ts_info;
    Movie mv = ts.movie;
    Time tm = ts.startTime;
    Time mv_end = addMinutes(tm, mv.duration);

    ts_info = getMovie(mv) + " [starts at " + getTime(tm) + ", ends by " + getTime(mv_end) + "]";

    return ts_info;
}

TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie) {
    /*
    The function should produce and return a new TimeSlot for the movie nextMovie, 
    scheduled immediately after the time slot ts.
    */
    
    Time time = addMinutes(ts.startTime, ts.movie.duration);
    TimeSlot new_ts = {nextMovie, time};
    return new_ts;
}

bool timeOverlap(TimeSlot ts1, TimeSlot ts2) {
    //The function should return true if the two time slots overlap, otherwise return false. 
    int time_bet, mov_time;
    int ts1_start = minutesSinceMidnight(ts1.startTime);
    int ts2_start = minutesSinceMidnight(ts2.startTime);

    if (ts1_start > ts2_start) { // ts2 starts before ts1
        time_bet = ts1_start - ts2_start;
        mov_time = ts2.movie.duration;
    } else { // ts1 starts before or at the same time as ts2
        time_bet = ts2_start - ts1_start;
        mov_time = ts1.movie.duration;
    }

    // if the movie is longer than the time between the two timeslots, return true (there is overlap), 
    // else return false (there is no overlap)
    return (time_bet < mov_time);
}