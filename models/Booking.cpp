#include "Booking.h"

Booking::Booking(): aintBookingID(0), aintTourID(0), aintCustomerID(0), aintStaffID(0), aintQuantity(0), adblTotal(0.0), astrBookingDate(""), astrStatus("") {}

Booking::Booking(int theIntTourID, int theIntCustomerID, int theIntStaffID, int theIntQuantity, double theDblTotal)
    : aintBookingID(0), aintTourID(theIntTourID), aintCustomerID(theIntCustomerID), aintStaffID(theIntStaffID), aintQuantity(theIntQuantity), adblTotal(theDblTotal), astrBookingDate(""), astrStatus("") {}
