#include <iostream>
#include <cassert>
#include "../controllers/storage.h"

int main() {
    Storage theStorage;

    // Prepare referenced data
    Tour t1("T1", 100.0, 10); addTour(theStorage, t1); // id 1
    Customer c1("C1"); addCustomer(theStorage, c1); // id 1
    Staff s1("S1"); addStaff(theStorage, s1); // id 1

    // Test 1: add booking and check ID
    Booking b1(1,1,1,2,200.0);
    int aintB1 = addBooking(theStorage, b1);
    assert(aintB1 == 1);

    // Test 2: booking stored and lookup
    Booking* pb = findBookingByID(theStorage, aintB1);
    assert(pb != nullptr);
    assert(pb->aintQuantity == 2);

    // Test 3: FK prevention for tour deletion
    bool removed = removeTour(theStorage, 1);
    assert(!removed); // has booking

    // Test 4: remove booking then remove tour
    bool removedB = removeBooking(theStorage, aintB1);
    assert(removedB);
    removed = removeTour(theStorage, 1);
    assert(removed);

    // Test 5: attempt invalid booking (referencing non-existent IDs) should still be added by storage layer
    Booking b2(999,999,999,1,100.0);
    int aintB2 = addBooking(theStorage, b2);
    assert(aintB2 == 2);
    // higher level should validate, storage accepts any IDs

    std::cout << "test_booking: all tests passed\n";
    return 0;
}
