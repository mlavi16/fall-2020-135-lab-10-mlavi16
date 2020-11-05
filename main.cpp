#include "time.h"
#include "movie.h"
#include "timeslot.h"
#include <iostream>

void printTime(Time time);
void printMovie(Movie mv);

int main()
{
    std::cout << "There are " << minutesSinceMidnight({14, 20}) << " minutes from 00:00 to 14:20." << std::endl; //should return 860
    
    std::cout << "There are " << minutesUntil( {10, 30}, {13, 40} ) << " minutes between 10:30 and 13:40." << std::endl; //should return 190
    
    Time time = addMinutes({8, 10}, 75);
    std::cout << "Seventy Five (75) minutes after 8:10 is " << time.h << ":" << time.m << "." << std::endl; // should return {9, 25}
    
    std::cout << getTimeSlot({{"Inception", ACTION, 1000}, {9, 15}}) << std::endl;

    TimeSlot ts = scheduleAfter({{"movie!!", COMEDY, 120}, {14, 10}}, {"film", ROMANCE, 60});
    std::cout << "The next timeslot after 14:10 is " << ts.startTime.h << ":" << ts.startTime.m << std::endl;

    TimeSlot ts1 = {{"hoopla", DRAMA, 120}, {14, 10}};
    TimeSlot ts2 = {{"wowzers", ROMANCE, 120}, {15, 30}};
    std::cout << "The movie timeslot [14:10, 16:10]";
    if (timeOverlap(ts1, ts2)) {
        std::cout << " overlaps ";
    } else {
        std::cout << " does not overlap ";
    }
    std::cout << "with the timeslot [15:30, 17:30]" << std::endl;

    return 0;
}

// void printTime(Time time) {
//     std::cout << time.h << ":" << time.m;
// }

// void printMovie(Movie mv){
//     std::string g;
//     switch (mv.genre) {
//         case ACTION   : g = "ACTION"; break;
//         case COMEDY   : g = "COMEDY"; break;
//         case DRAMA    : g = "DRAMA";  break;
//         case ROMANCE  : g = "ROMANCE"; break;
//         case THRILLER : g = "THRILLER"; break;
//     }
//     std::cout << mv.title << " " << g << " (" << mv.duration << " min)";
// }
