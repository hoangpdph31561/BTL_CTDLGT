#pragma once
#include <string>

struct Customer {
    int aintCustomerID;
    std::string astrCustomerName;
    std::string astrPhone;
    std::string astrEmail;
    std::string astrAddress;
    std::string astrBirthDate;
    std::string astrMemberType;

    Customer();
    Customer(const std::string &theStrName);
};
