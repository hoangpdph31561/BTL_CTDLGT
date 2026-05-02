#include <iostream>
#include <cassert>
#include "../controllers/storage.h"

int main() {
    Storage s;
    // generate sample data once
    bool gen = generateSampleDataOnce(s);
    assert(gen == true);

    // create booking for tour 1, customer 1, staff 1
    Booking b1(1,1,1,2,2 * 120.0);
    int idB = addBooking(s, b1);
    assert(idB == 1);

    // FK prevention: cannot remove tour 1
    assert(hasBookingsForTour(s, 1) == true);
    assert(removeTour(s, 1) == false);

    // Remove booking then remove tour
    assert(removeBooking(s, idB) == true);
    assert(hasBookingsForTour(s, 1) == false);
    assert(removeTour(s, 1) == true);

    // generate sample data again should be blocked
    assert(generateSampleDataOnce(s) == false);

    std::cout << "test_menu_flow: all tests passed\n";
    return 0;
}
