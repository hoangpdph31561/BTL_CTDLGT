#pragma once
#include <string>

struct Booking {
    int aintBookingID;
    int aintTourID;
    int aintCustomerID;
    int aintStaffID;
    int aintQuantity;
    double adblTotal;
    std::string astrBookingDate;
    std::string astrStatus;

    Booking();
    Booking(int theIntTourID, int theIntCustomerID, int theIntStaffID, int theIntQuantity, double theDblTotal);
};
