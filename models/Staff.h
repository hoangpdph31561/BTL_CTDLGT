#pragma once
#include <string>

struct Staff {
    int aintStaffID;
    std::string astrStaffName;
    std::string astrPosition;
    std::string astrPhone;
    std::string astrEmail;
    std::string astrUsername;

    Staff();
    Staff(const std::string &theStrName);
};
