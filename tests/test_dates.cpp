#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdio>
#include <string>
#include "../controllers/storage.h"
#include "../controllers/menu.h" // menu.h already exposes parseDateToInt and todayDateInt

int main() {
    Storage s;
    // generate sample data
    bool ok = generateSampleDataOnce(s);
    assert(ok == true);
    // sample tours have dates set in storage.generate
    Tour* t1 = findTourByID(s, 1);
    assert(t1 != nullptr);
    int aintStart = parseDateToInt(t1->astrStartDate);
    int aintEnd = parseDateToInt(t1->astrEndDate);
    assert(aintStart != 0 && aintEnd != 0 && aintEnd >= aintStart);

    // booking on past date should be rejected at menu level; storage can accept but we check parse
    int bad = parseDateToInt("311220" /* invalid */);
    assert(bad == 0);

    // booking date within range
    int today = todayDateInt();
    // create booking with today's date as string in DDMMYYYY
    char buf[9];
    std::time_t t = std::time(nullptr);
    std::tm local;
#if defined(_WIN32)
    localtime_s(&local, &t);
#else
    local = *std::localtime(&t);
#endif
    int d = local.tm_mday, m = local.tm_mon+1, y = local.tm_year+1900;
    sprintf(buf, "%02d%02d%04d", d, m, y);
    std::string todayStr(buf);

    Booking b(todayStr.size()?1:0, 1, 1, 1, 100.0); // dummy, not used
    // we simply test parseDateToInt on today's string
    int parsed = parseDateToInt(todayStr);
    assert(parsed != 0);

    std::cout << "test_dates: all tests passed\n";
    return 0;
}
