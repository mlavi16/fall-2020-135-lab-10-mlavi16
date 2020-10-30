#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "time.h"

bool equal_time(Time time1, Time time2) {
    return time1.h == time2.h && time1.m == time2.m;
}

TEST_CASE("minutesSinceMidnight(Time time)") {
    CHECK(minutesSinceMidnight({0, 0}) == 0);
    CHECK(minutesSinceMidnight({10, 14}) == 614);
    //TODO 
    //Test negative time?
    //Test time > 24
}

TEST_CASE("minutesUntil(Time earlier, Time later") {
    CHECK(minutesUntil({3, 12}, {5, 19}) == 127);
    CHECK(minutesUntil({10, 10}, {10, 10}) == 0);
    CHECK(minutesUntil({10, 30}, {8, 0}) == -150);
}

TEST_CASE("addMinutes(Time time0, int min)") {
    CHECK(equal_time(addMinutes({10, 30}, 0), {10, 30}));

    CHECK(equal_time(addMinutes({3, 40}, 19), {3, 59}));
    CHECK(equal_time(addMinutes({3, 40}, 20), {4, 0}));
    CHECK(equal_time(addMinutes({3, 40}, 21), {4, 1}));

    CHECK(equal_time(addMinutes({23, 40}, 90), {1, 10}));

    CHECK(equal_time(addMinutes({6, 30}, -90), {5, 0}));
}