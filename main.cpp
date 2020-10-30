#include "time.h"
#include <iostream>

int main()
{

    std::cout << "There are " << minutesSinceMidnight({14, 20}) << " minutes from 00:00 to 14:20." << std::endl; //should return 860
    std::cout << "There are " << minutesUntil( {10, 30}, {13, 40} ) << " minutes between 10:30 and 13:40." << std::endl; //should return 190
    Time time = addMinutes({8, 10}, 75);
    std::cout << "Seventy Five (75) minutes after 8:10 is " << time.h << ":" << time.m << "." << std::endl; // should return {9, 25}

    return 0;
}