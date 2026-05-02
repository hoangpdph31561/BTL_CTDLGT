#pragma once
#include <string>

struct Tour {
    int aintTourID;
    std::string astrTourName;
    std::string astrOrigin;
    std::string astrDestination;
    std::string astrStartDate;
    std::string astrEndDate;
    double adblPrice;
    int aintCapacity;
    std::string astrStatus;
    std::string astrDescription;

    Tour();
    Tour(const std::string &theStrName, double theDblPrice, int theIntCapacity);
};
