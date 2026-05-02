#include "Staff.h"

Staff::Staff(): aintStaffID(0), astrStaffName(""), astrPosition(""), astrPhone(""), astrEmail(""), astrUsername("") {}

Staff::Staff(const std::string &theStrName): aintStaffID(0), astrStaffName(theStrName), astrPosition(""), astrPhone(""), astrEmail(""), astrUsername("") {}
