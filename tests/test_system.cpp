#include <iostream>
#include <cassert>
#include "../controllers/storage.h"

int main() {
    Storage theStorage;

    // System scenario: create data, create bookings, delete operations
    int idT = addTour(theStorage, Tour("Sapa Trip", 80.0, 15));
    int idC = addCustomer(theStorage, Customer("Pham A"));
    int idS = addStaff(theStorage, Staff("Hoang B"));

    int idB = addBooking(theStorage, Booking(idT, idC, idS, 4, 4 * 80.0));

    // View booking with joined info
    Booking* pb = findBookingByID(theStorage, idB);
    assert(pb != nullptr);
    Tour* pt = findTourByID(theStorage, pb->aintTourID);
    assert(pt->adblPrice == 80.0);

    // Attempt to delete customer referenced by booking -> blocked
    bool removed = removeCustomer(theStorage, idC);
    assert(!removed);

    // Cleanup: remove booking, then remove customer
    assert(removeBooking(theStorage, idB));
    assert(removeCustomer(theStorage, idC));

    std::cout << "test_system: all tests passed\n";
    return 0;
}
