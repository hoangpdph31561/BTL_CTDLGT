#include "Tour.h"

Tour::Tour(): aintTourID(0), astrTourName(""), astrOrigin(""), astrDestination(""), astrStartDate(""), astrEndDate(""), adblPrice(0.0), aintCapacity(0), astrStatus(""), astrDescription("") {}

Tour::Tour(const std::string &theStrName, double theDblPrice, int theIntCapacity)
    : aintTourID(0), astrTourName(theStrName), astrOrigin(""), astrDestination(""), astrStartDate(""), astrEndDate(""), adblPrice(theDblPrice), aintCapacity(theIntCapacity), astrStatus(""), astrDescription("") {}
