#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "time.h"
#include "movie.h"
#include "timeslot.h"

bool equal_time(Time time1, Time time2) {
    return time1.h == time2.h && time1.m == time2.m;
}

bool equal_movie(Movie movie1, Movie movie2) {
    return movie1.duration == movie2.duration && movie1.genre == movie2.genre && movie1.title == movie2.title;
}

bool equal_timeSlot(TimeSlot ts1, TimeSlot ts2) {
    return equal_time(ts1.startTime, ts2.startTime) && equal_movie(ts1.movie, ts2.movie);
}

TEST_CASE("minutesSinceMidnight(Time time)") {
    CHECK(minutesSinceMidnight({0, 0}) == 0);
    CHECK(minutesSinceMidnight({10, 14}) == 614);
    CHECK(minutesSinceMidnight({25, 10}) == 70);
    CHECK(minutesSinceMidnight({2, 70}) == 190);
}

TEST_CASE("minutesUntil(Time earlier, Time later") {
    CHECK(minutesUntil({3, 12}, {5, 11}) == 119);
    CHECK(minutesUntil({3, 12}, {3, 19}) == 7);

    CHECK(minutesUntil({10, 10}, {10, 10}) == 0);
    CHECK(minutesUntil({0, 0}, {0, 0}) == 0);

    CHECK(minutesUntil({0, 0}, {24, 0}) == 0); // after 23:59, it goes back to 00:00 
    CHECK(minutesUntil({0, 12}, {25, 12}) == 60);

    CHECK(minutesUntil({4, 10}, {5, 80}) == 130); // 5:80 is the same as 6:20

    CHECK(minutesUntil({10, 30}, {8, 0}) == -150);
}

TEST_CASE("addMinutes(Time time0, int min)") {
    CHECK(equal_time(addMinutes({10, 30}, 480), {18, 30}));

    CHECK(equal_time(addMinutes({10, 30}, 0), {10, 30}));

    CHECK(equal_time(addMinutes({3, 40}, 19), {3, 59}));
    CHECK(equal_time(addMinutes({3, 40}, 20), {4, 0}));
    CHECK(equal_time(addMinutes({3, 40}, 21), {4, 1}));

    CHECK(equal_time(addMinutes({23, 40}, 90), {1, 10}));

    CHECK(equal_time(addMinutes({6, 30}, -90), {5, 0}));
    CHECK(equal_time(addMinutes({0, 0}, -61), {22, 59}));

    CHECK(equal_time(addMinutes({6, 63}, 0), {7, 3}));
}

TEST_CASE("getTimeSlot(TimeSlot ts)") {
    Movie mv1 = {"Who Framed Roger Rabbit", COMEDY, 104};
    Movie mv2 = {"The Princess Bride", ROMANCE, 98};
    Movie mv3 = {"Forrest Gump", DRAMA, 142};
    Movie mv4 = {"The Hobbit: An Unexpected Journey", ACTION, 169};
    Movie mv5 = {"Stardust", ROMANCE, 127};

    TimeSlot morning = {mv1, {9, 15}};
    TimeSlot midmorning = {mv2, {10, 30}};
    TimeSlot daytime = {mv2, {12, 15}};
    TimeSlot afternoon = {mv3, {14, 0}};
    TimeSlot evening = {mv4, {16, 45}};
    TimeSlot night = {mv5, {21, 30}};

    CHECK(getTimeSlot(morning) == "Who Framed Roger Rabbit COMEDY (104 min) [starts at 9:15, ends by 10:59]");
    CHECK(getTimeSlot(midmorning) == "The Princess Bride ROMANCE (98 min) [starts at 10:30, ends by 12:08]");
    CHECK(getTimeSlot(daytime) == "The Princess Bride ROMANCE (98 min) [starts at 12:15, ends by 13:53]");
    CHECK(getTimeSlot(afternoon) == "Forrest Gump DRAMA (142 min) [starts at 14:00, ends by 16:22]");
    CHECK(getTimeSlot(evening) == "The Hobbit: An Unexpected Journey ACTION (169 min) [starts at 16:45, ends by 19:34]");
    CHECK(getTimeSlot(night) == "Stardust ROMANCE (127 min) [starts at 21:30, ends by 23:37]");

    Time time = {1, 1};
    Movie movie = {"Hello World", ACTION, 10};
    CHECK(getTimeSlot({movie, time}) == "Hello World ACTION (10 min) [starts at 1:01, ends by 1:11]");

    time = {0, 000};
    movie = {"", COMEDY, 0};
    CHECK(getTimeSlot({movie, time}) == " COMEDY (0 min) [starts at 0:00, ends by 0:00]");
}

TEST_CASE("scheduleAfter(TimeSlot ts, Movie nextMovie)") {
    Movie mv1 = {"Titanic", ROMANCE, 120};
    Movie mv2 = {"Titanic 2", COMEDY, 110};

    CHECK(equal_timeSlot(scheduleAfter({mv1, {8, 15}}, mv2), {mv2, {10, 15}}));
    CHECK(equal_timeSlot(scheduleAfter({mv2, {8, 15}}, mv1), {mv1, {10, 5}}));

    CHECK(equal_timeSlot(scheduleAfter({mv1, {23, 15}}, mv2), {mv2, {1, 15}}));

    mv1.duration = 0;
    CHECK(equal_timeSlot(scheduleAfter({mv1, {8, 15}}, mv2), {mv2, {8, 15}}));
    CHECK(equal_timeSlot(scheduleAfter({mv1, {0, 0}}, mv2), {mv2, {0, 0}}));

    mv1.duration = -15;
    CHECK(equal_timeSlot(scheduleAfter({mv1, {8, 15}}, mv2), {mv2, {8, 0}}));
}

TEST_CASE("timeOverlap(TimeSlot ts1, TimeSlot ts2)") {
    Movie mv1 = {"James Bond", ACTION, 182};
    Movie mv2 = {"Harry Potter", DRAMA, 126};
    CHECK(timeOverlap({mv1, {9, 15}}, {mv2, {20, 0}}) == false);
    CHECK(timeOverlap({mv1, {20, 15}}, {mv2, {10, 30}}) == false);
    CHECK(timeOverlap({mv1, {12, 0}}, {mv2, {15, 2}}) == false); // mv1 ends at the same time mv2 starts (15:02)
    CHECK(timeOverlap({mv1, {23, 15}}, {mv2, {1, 0}}) == false); //mv2 starts 22 hrs before mv1, mv1 goes into next day so no overlap
    CHECK(timeOverlap({mv1, {15, 32}}, {mv2, {12, 30}}) == false);


    CHECK(timeOverlap({mv1, {9, 15}}, {mv2, {10, 30}}) == true);
    CHECK(timeOverlap({mv1, {12, 0}}, {mv2, {15, 1}}) == true); //mv1 ends at 15:02, mv2 starts at 15:01
    CHECK(timeOverlap({mv1, {9, 15}}, {mv2, {9, 15}}) == true);
    CHECK(timeOverlap({mv1, {9, 15}}, {mv2, {8, 15}}) == true);

    mv1.duration = 0;
    CHECK(timeOverlap({mv1, {9, 15}}, {mv2, {9, 15}}) == false);
}