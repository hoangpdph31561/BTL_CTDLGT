#include <iostream>
#include <cassert>
#include "../controllers/storage.h"

int main() {
    Storage theStorage;

    // Create tours, customers, staff
    Tour t1("Hai Phong Tour", 120.0, 20); int idT1 = addTour(theStorage, t1);
    Customer c1("Tran Van X"); int idC1 = addCustomer(theStorage, c1);
    Staff s1("Nguyen NV"); int idS1 = addStaff(theStorage, s1);

    // Create multiple bookings
    Booking b1(idT1, idC1, idS1, 3, 3 * 120.0); int idB1 = addBooking(theStorage, b1);
    Booking b2(idT1, idC1, idS1, 2, 2 * 120.0); int idB2 = addBooking(theStorage, b2);

    // Integration test: total revenue for tour idT1
    double adblRevenue = 0.0;
    for (const auto &bk : theStorage.bookings) if (bk.aintTourID == idT1) adblRevenue += bk.adblTotal;
    assert(adblRevenue == 5 * 120.0);

    // Test lookup join-like printing
    Booking* pb = findBookingByID(theStorage, idB1);
    assert(pb != nullptr);
    Tour* pt = findTourByID(theStorage, pb->aintTourID);
    Customer* pc = findCustomerByID(theStorage, pb->aintCustomerID);
    Staff* ps = findStaffByID(theStorage, pb->aintStaffID);
    assert(pt != nullptr && pc != nullptr && ps != nullptr);

    std::cout << "test_integration: all tests passed\n";
    return 0;
}
