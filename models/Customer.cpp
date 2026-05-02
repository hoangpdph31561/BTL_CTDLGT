#include "Customer.h"

Customer::Customer(): aintCustomerID(0), astrCustomerName(""), astrPhone(""), astrEmail(""), astrAddress(""), astrBirthDate(""), astrMemberType("") {}

Customer::Customer(const std::string &theStrName): aintCustomerID(0), astrCustomerName(theStrName), astrPhone(""), astrEmail(""), astrAddress(""), astrBirthDate(""), astrMemberType("") {}
