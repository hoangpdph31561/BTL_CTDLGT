#include "storage.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

int addTour(Storage &theStorage, const Tour &theTour) {
    Tour local = theTour;
    local.aintTourID = theStorage.myIntNextTourID++;
    theStorage.tours.push_back(local);
    return local.aintTourID;
}

int addCustomer(Storage &theStorage, const Customer &theCustomer) {
    Customer local = theCustomer;
    local.aintCustomerID = theStorage.myIntNextCustomerID++;
    theStorage.customers.push_back(local);
    return local.aintCustomerID;
}

int addStaff(Storage &theStorage, const Staff &theStaff) {
    Staff local = theStaff;
    local.aintStaffID = theStorage.myIntNextStaffID++;
    theStorage.staffs.push_back(local);
    return local.aintStaffID;
}

int addBooking(Storage &theStorage, const Booking &theBooking) {
    Booking local = theBooking;
    local.aintBookingID = theStorage.myIntNextBookingID++;
    theStorage.bookings.push_back(local);
    return local.aintBookingID;
}

bool hasBookingsForTour(const Storage &theStorage, int aintTourID) {
    for (const auto &b : theStorage.bookings) if (b.aintTourID == aintTourID) return true;
    return false;
}

bool hasBookingsForCustomer(const Storage &theStorage, int aintCustomerID) {
    for (const auto &b : theStorage.bookings) if (b.aintCustomerID == aintCustomerID) return true;
    return false;
}

bool hasBookingsForStaff(const Storage &theStorage, int aintStaffID) {
    for (const auto &b : theStorage.bookings) if (b.aintStaffID == aintStaffID) return true;
    return false;
}

void listToursForSelection(const Storage &theStorage) {
    std::cout << "ID | Name | Destination | Start | Price | Capacity\n";
    for (const auto &t : theStorage.tours) {
        std::cout << t.aintTourID << " | " << t.astrTourName << " | " << t.astrDestination << " | " << t.astrStartDate << " | " << t.adblPrice << " | " << t.aintCapacity << "\n";
    }
}

void listCustomersForSelection(const Storage &theStorage) {
    std::cout << "ID | Name | Phone | Email\n";
    for (const auto &c : theStorage.customers) {
        std::cout << c.aintCustomerID << " | " << c.astrCustomerName << " | " << c.astrPhone << " | " << c.astrEmail << "\n";
    }
}

void listStaffForSelection(const Storage &theStorage) {
    std::cout << "ID | Name | Position | Phone\n";
    for (const auto &s : theStorage.staffs) {
        std::cout << s.aintStaffID << " | " << s.astrStaffName << " | " << s.astrPosition << " | " << s.astrPhone << "\n";
    }
}

Tour* findTourByID(Storage &theStorage, int aintTourID) {
    for (auto &t : theStorage.tours) if (t.aintTourID == aintTourID) return &t;
    return nullptr;
}

Customer* findCustomerByID(Storage &theStorage, int aintCustomerID) {
    for (auto &c : theStorage.customers) if (c.aintCustomerID == aintCustomerID) return &c;
    return nullptr;
}

Staff* findStaffByID(Storage &theStorage, int aintStaffID) {
    for (auto &s : theStorage.staffs) if (s.aintStaffID == aintStaffID) return &s;
    return nullptr;
}

Booking* findBookingByID(Storage &theStorage, int aintBookingID) {
    for (auto &b : theStorage.bookings) if (b.aintBookingID == aintBookingID) return &b;
    return nullptr;
}

bool removeTour(Storage &theStorage, int aintTourID) {
    if (hasBookingsForTour(theStorage, aintTourID)) return false;
    auto it = std::remove_if(theStorage.tours.begin(), theStorage.tours.end(), [aintTourID](const Tour &t){ return t.aintTourID == aintTourID; });
    if (it == theStorage.tours.end()) return false;
    theStorage.tours.erase(it, theStorage.tours.end());
    return true;
}

bool removeCustomer(Storage &theStorage, int aintCustomerID) {
    if (hasBookingsForCustomer(theStorage, aintCustomerID)) return false;
    auto it = std::remove_if(theStorage.customers.begin(), theStorage.customers.end(), [aintCustomerID](const Customer &c){ return c.aintCustomerID == aintCustomerID; });
    if (it == theStorage.customers.end()) return false;
    theStorage.customers.erase(it, theStorage.customers.end());
    return true;
}

bool removeStaff(Storage &theStorage, int aintStaffID) {
    if (hasBookingsForStaff(theStorage, aintStaffID)) return false;
    auto it = std::remove_if(theStorage.staffs.begin(), theStorage.staffs.end(), [aintStaffID](const Staff &s){ return s.aintStaffID == aintStaffID; });
    if (it == theStorage.staffs.end()) return false;
    theStorage.staffs.erase(it, theStorage.staffs.end());
    return true;
}

bool removeBooking(Storage &theStorage, int aintBookingID) {
    auto it = std::remove_if(theStorage.bookings.begin(), theStorage.bookings.end(), [aintBookingID](const Booking &b){ return b.aintBookingID == aintBookingID; });
    if (it == theStorage.bookings.end()) return false;
    theStorage.bookings.erase(it, theStorage.bookings.end());
    return true;
}

bool generateSampleDataOnce(Storage &theStorage) {
    if (theStorage.myBoolSampleDataGenerated) return false;

    // Add ~10 tours
    std::vector<Tour> avTours = {
        Tour("Ha Long Bay", 120.0, 30),
        Tour("Da Nang Escape", 90.0, 20),
        Tour("Sapa Adventure", 150.0, 25),
        Tour("Phu Quoc Relax", 200.0, 40),
        Tour("Ninh Binh Discovery", 80.0, 20),
        Tour("Hue Heritage", 95.0, 18),
        Tour("Mekong Delta", 110.0, 30),
        Tour("Ho Chi Minh City Tour", 70.0, 50),
        Tour("Da Lat Retreat", 130.0, 22),
        Tour("Hanoi Classic", 85.0, 35)
    };

    // set extra fields (origin, destination, start/end)
    avTours[0].astrOrigin = "Hanoi"; avTours[0].astrDestination = "Ha Long"; avTours[0].astrStartDate = "01062026"; avTours[0].astrEndDate = "05062026";
    avTours[1].astrOrigin = "Da Nang"; avTours[1].astrDestination = "Da Nang"; avTours[1].astrStartDate = "10072026"; avTours[1].astrEndDate = "15072026";
    avTours[2].astrOrigin = "Hanoi"; avTours[2].astrDestination = "Sapa"; avTours[2].astrStartDate = "20062026"; avTours[2].astrEndDate = "23062026";
    avTours[3].astrOrigin = "Ho Chi Minh"; avTours[3].astrDestination = "Phu Quoc"; avTours[3].astrStartDate = "01082026"; avTours[3].astrEndDate = "05082026";
    avTours[4].astrOrigin = "Ninh Binh"; avTours[4].astrDestination = "Ninh Binh"; avTours[4].astrStartDate = "15062026"; avTours[4].astrEndDate = "16062026";
    avTours[5].astrOrigin = "Hue"; avTours[5].astrDestination = "Hue"; avTours[5].astrStartDate = "05092026"; avTours[5].astrEndDate = "07092026";
    avTours[6].astrOrigin = "Can Tho"; avTours[6].astrDestination = "Mekong"; avTours[6].astrStartDate = "12072026"; avTours[6].astrEndDate = "14072026";
    avTours[7].astrOrigin = "Ho Chi Minh"; avTours[7].astrDestination = "HCMC"; avTours[7].astrStartDate = "01062026"; avTours[7].astrEndDate = "01062026";
    avTours[8].astrOrigin = "Da Lat"; avTours[8].astrDestination = "Da Lat"; avTours[8].astrStartDate = "20082026"; avTours[8].astrEndDate = "22082026";
    avTours[9].astrOrigin = "Hanoi"; avTours[9].astrDestination = "Hanoi"; avTours[9].astrStartDate = "05062026"; avTours[9].astrEndDate = "06062026";

    for (const auto &theT : avTours) addTour(theStorage, theT);

    // Add ~10 customers
    std::vector<Customer> avCustomers = {
        Customer("Nguyen Van A"), Customer("Tran Thi B"), Customer("Le Van C"), Customer("Pham Thi D"), Customer("Hoang Van E"),
        Customer("Ngo Thi F"), Customer("Vu Van G"), Customer("Do Thi H"), Customer("Bui Van I"), Customer("Duong Thi J")
    };
    // add phones/emails
    avCustomers[0].astrPhone = "0123456789"; avCustomers[0].astrEmail = "a@example.com";
    avCustomers[1].astrPhone = "0987654321"; avCustomers[1].astrEmail = "b@example.com";
    avCustomers[2].astrPhone = "0911222333"; avCustomers[2].astrEmail = "c@example.com";
    avCustomers[3].astrPhone = "0944556677"; avCustomers[3].astrEmail = "d@example.com";
    avCustomers[4].astrPhone = "0977888999"; avCustomers[4].astrEmail = "e@example.com";
    avCustomers[5].astrPhone = "0900111222"; avCustomers[5].astrEmail = "f@example.com";
    avCustomers[6].astrPhone = "0933444555"; avCustomers[6].astrEmail = "g@example.com";
    avCustomers[7].astrPhone = "0955667788"; avCustomers[7].astrEmail = "h@example.com";
    avCustomers[8].astrPhone = "0922333444"; avCustomers[8].astrEmail = "i@example.com";
    avCustomers[9].astrPhone = "0966778899"; avCustomers[9].astrEmail = "j@example.com";

    for (const auto &theC : avCustomers) addCustomer(theStorage, theC);

    // Add ~10 staff
    std::vector<Staff> avStaff = {
        Staff("Le Thi B"), Staff("Tran Van K"), Staff("Nguyen Thi L"), Staff("Pham Van M"), Staff("Hoang Thi N"),
        Staff("Vu Van O"), Staff("Do Thi P"), Staff("Bui Van Q"), Staff("Duong Thi R"), Staff("Ngo Van S")
    };
    avStaff[0].astrPosition = "Sales"; avStaff[0].astrPhone = "0111000111"; avStaff[0].astrEmail = "staff1@agency.com";
    avStaff[1].astrPosition = "Guide"; avStaff[1].astrPhone = "0111000222"; avStaff[1].astrEmail = "staff2@agency.com";
    avStaff[2].astrPosition = "Sales"; avStaff[2].astrPhone = "0111000333"; avStaff[2].astrEmail = "staff3@agency.com";
    avStaff[3].astrPosition = "Manager"; avStaff[3].astrPhone = "0111000444"; avStaff[3].astrEmail = "staff4@agency.com";
    avStaff[4].astrPosition = "Guide"; avStaff[4].astrPhone = "0111000555"; avStaff[4].astrEmail = "staff5@agency.com";
    avStaff[5].astrPosition = "Sales"; avStaff[5].astrPhone = "0111000666"; avStaff[5].astrEmail = "staff6@agency.com";
    avStaff[6].astrPosition = "Guide"; avStaff[6].astrPhone = "0111000777"; avStaff[6].astrEmail = "staff7@agency.com";
    avStaff[7].astrPosition = "Sales"; avStaff[7].astrPhone = "0111000888"; avStaff[7].astrEmail = "staff8@agency.com";
    avStaff[8].astrPosition = "Support"; avStaff[8].astrPhone = "0111000999"; avStaff[8].astrEmail = "staff9@agency.com";
    avStaff[9].astrPosition = "Guide"; avStaff[9].astrPhone = "0111001111"; avStaff[9].astrEmail = "staff10@agency.com";

    for (const auto &theS : avStaff) addStaff(theStorage, theS);

    // Add several bookings referencing created tours/customers/staff
    // Use available IDs (auto-incremented by addTour/addCustomer/addStaff)
    // Create a few bookings across tours
    if (!theStorage.tours.empty() && !theStorage.customers.empty() && !theStorage.staffs.empty()) {
        // choose some ids
        int aintTour1 = theStorage.tours[0].aintTourID;
        int aintTour2 = theStorage.tours[1].aintTourID;
        int aintTour3 = theStorage.tours[2].aintTourID;
        int aintCust1 = theStorage.customers[0].aintCustomerID;
        int aintCust2 = theStorage.customers[1].aintCustomerID;
        int aintCust3 = theStorage.customers[2].aintCustomerID;
        int aintStaff1 = theStorage.staffs[0].aintStaffID;
        int aintStaff2 = theStorage.staffs[1].aintStaffID;
        int aintStaff3 = theStorage.staffs[2].aintStaffID;

        Booking b1(aintTour1, aintCust1, aintStaff1, 2, theStorage.tours[0].adblPrice * 2);
        b1.astrBookingDate = theStorage.tours[0].astrStartDate; b1.astrStatus = "confirmed"; addBooking(theStorage, b1);

        Booking b2(aintTour1, aintCust2, aintStaff2, 4, theStorage.tours[0].adblPrice * 4);
        b2.astrBookingDate = theStorage.tours[0].astrStartDate; b2.astrStatus = "pending"; addBooking(theStorage, b2);

        Booking b3(aintTour2, aintCust3, aintStaff1, 1, theStorage.tours[1].adblPrice * 1);
        b3.astrBookingDate = theStorage.tours[1].astrStartDate; b3.astrStatus = "confirmed"; addBooking(theStorage, b3);

        Booking b4(aintTour3, aintCust1, aintStaff3, 3, theStorage.tours[2].adblPrice * 3);
        b4.astrBookingDate = theStorage.tours[2].astrStartDate; b4.astrStatus = "canceled"; addBooking(theStorage, b4);

        // more varied bookings
        // create additional bookings using indices safely
        for (size_t ai = 3; ai < theStorage.tours.size() && ai < theStorage.customers.size() && ai < theStorage.staffs.size() && ai < 8; ++ai) {
            int aintTid = theStorage.tours[ai].aintTourID;
            int aintCid = theStorage.customers[ai].aintCustomerID;
            int aintSid = theStorage.staffs[ai].aintStaffID;
            int aintQty = (int)(1 + (ai % 4));
            double adblTot = theStorage.tours[ai].adblPrice * aintQty;
            Booking theB(aintTid, aintCid, aintSid, aintQty, adblTot);
            theB.astrBookingDate = theStorage.tours[ai].astrStartDate;
            theB.astrStatus = (ai % 3 == 0) ? "confirmed" : ((ai % 3 == 1) ? "pending" : "canceled");
            addBooking(theStorage, theB);
        }
    }

    theStorage.myBoolSampleDataGenerated = true;
    return true;
}

// save storage to text file
bool saveStorageToFile(const Storage &theStorage, const std::string &theFilePath) {
    std::ofstream ofs(theFilePath);
    if (!ofs.is_open()) return false;
    ofs << "# Tours\n";
    for (const auto &t : theStorage.tours) {
        ofs << t.aintTourID << "|" << t.astrTourName << "|" << t.astrOrigin << "|" << t.astrDestination << "|" << t.astrStartDate << "|" << t.astrEndDate << "|" << t.adblPrice << "|" << t.aintCapacity << "\n";
    }
    ofs << "# Customers\n";
    for (const auto &c : theStorage.customers) {
        ofs << c.aintCustomerID << "|" << c.astrCustomerName << "|" << c.astrPhone << "|" << c.astrEmail << "|" << c.astrAddress << "\n";
    }
    ofs << "# Staffs\n";
    for (const auto &s : theStorage.staffs) {
        ofs << s.aintStaffID << "|" << s.astrStaffName << "|" << s.astrPosition << "|" << s.astrPhone << "|" << s.astrEmail << "\n";
    }
    ofs << "# Bookings\n";
    for (const auto &b : theStorage.bookings) {
        ofs << b.aintBookingID << "|" << b.aintTourID << "|" << b.aintCustomerID << "|" << b.aintStaffID << "|" << b.aintQuantity << "|" << b.adblTotal << "|" << b.astrBookingDate << "|" << b.astrStatus << "\n";
    }
    ofs.close();
    return true;
}

bool loadStorageFromFile(Storage &theStorage, const std::string &theFilePath) {
    std::ifstream ifs(theFilePath);
    if (!ifs.is_open()) {
        return false;
    }
    std::cout << "--- Contents of file: " << theFilePath << " ---\n";
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << "\n";
    }
    std::cout << "--- End of file ---\n";
    ifs.close();
    return true;
}

std::vector<Tour> getToursSortedByPrice(const Storage &theStorage, bool theBoolDesc) {
    std::vector<Tour> avOut = theStorage.tours;
    std::sort(avOut.begin(), avOut.end(), [theBoolDesc](const Tour &a, const Tour &b){
        if (theBoolDesc) return a.adblPrice > b.adblPrice; else return a.adblPrice < b.adblPrice;
    });
    return avOut;
}

std::vector<Tour> getToursSortedByStartDate(const Storage &theStorage, bool theBoolDesc) {
    auto parse = [](const std::string &astrS){
        if (astrS.size() != 8) return 0;
        try { int aintD = std::stoi(astrS.substr(0,2)); int aintM = std::stoi(astrS.substr(2,2)); int aintY = std::stoi(astrS.substr(4,4)); return aintY*10000 + aintM*100 + aintD; } catch(...) { return 0; }
    };
    std::vector<Tour> avOut = theStorage.tours;
    std::sort(avOut.begin(), avOut.end(), [theBoolDesc,&parse](const Tour &theA, const Tour &theB){
        int aintA = parse(theA.astrStartDate); int aintB = parse(theB.astrStartDate);
        if (theBoolDesc) return aintA > aintB; else return aintA < aintB;
    });
    return avOut;
}

std::vector<Customer> getCustomersSortedByName(const Storage &theStorage, bool theBoolDesc) {
    std::vector<Customer> avOut = theStorage.customers;
    std::sort(avOut.begin(), avOut.end(), [theBoolDesc](const Customer &theA, const Customer &theB){
        if (theBoolDesc) return theA.astrCustomerName > theB.astrCustomerName; else return theA.astrCustomerName < theB.astrCustomerName;
    });
    return avOut;
}

std::vector<Booking> getBookingsSortedByDate(const Storage &theStorage, bool theBoolDesc) {
    auto parse = [](const std::string &astrS){ if (astrS.size()!=8) return 0; try{ int aintD=std::stoi(astrS.substr(0,2)); int aintM=std::stoi(astrS.substr(2,2)); int aintY=std::stoi(astrS.substr(4,4)); return aintY*10000+aintM*100+aintD;}catch(...){return 0;} };
    std::vector<Booking> avOut = theStorage.bookings;
    std::sort(avOut.begin(), avOut.end(), [theBoolDesc,&parse](const Booking &theA, const Booking &theB){ int aintA=parse(theA.astrBookingDate); int aintB=parse(theB.astrBookingDate); if (theBoolDesc) return aintA>aintB; else return aintA<aintB; });
    return avOut;
}

const Tour* getTourWithMaxPrice(const Storage &theStorage) {
    if (theStorage.tours.empty()) return nullptr;
    return &(*std::max_element(theStorage.tours.begin(), theStorage.tours.end(), [](const Tour &theA,const Tour &theB){ return theA.adblPrice < theB.adblPrice; }));
}

const Tour* getTourWithMinPrice(const Storage &theStorage) {
    if (theStorage.tours.empty()) return nullptr;
    return &(*std::min_element(theStorage.tours.begin(), theStorage.tours.end(), [](const Tour &theA,const Tour &theB){ return theA.adblPrice < theB.adblPrice; }));
}

const Tour* getTourWithMaxCapacity(const Storage &theStorage) {
    if (theStorage.tours.empty()) return nullptr;
    return &(*std::max_element(theStorage.tours.begin(), theStorage.tours.end(), [](const Tour &theA,const Tour &theB){ return theA.aintCapacity < theB.aintCapacity; }));
}

const Booking* getBookingWithMaxTotal(const Storage &theStorage) {
    if (theStorage.bookings.empty()) return nullptr;
    return &(*std::max_element(theStorage.bookings.begin(), theStorage.bookings.end(), [](const Booking &theA,const Booking &theB){ return theA.adblTotal < theB.adblTotal; }));
}

double totalRevenue(const Storage &theStorage) {
    double adblSum = 0.0; for (const auto &theB : theStorage.bookings) adblSum += theB.adblTotal; return adblSum;
}

double averageRevenuePerBooking(const Storage &theStorage) {
    if (theStorage.bookings.empty()) return 0.0; return totalRevenue(theStorage) / (double)theStorage.bookings.size();
}

int countTours(const Storage &theStorage) { return (int)theStorage.tours.size(); }
int countCustomers(const Storage &theStorage) { return (int)theStorage.customers.size(); }

int totalGuestsBooked(const Storage &theStorage) { int aintSum=0; for (const auto &theB : theStorage.bookings) aintSum += theB.aintQuantity; return aintSum; }

std::map<int,double> revenuePerTour(const Storage &theStorage) {
    std::map<int,double> am;
    for (const auto &theB : theStorage.bookings) am[theB.aintTourID] += theB.adblTotal;
    return am;
}

std::map<int,int> bookingsPerCustomer(const Storage &theStorage) {
    std::map<int,int> am; for (const auto &theB : theStorage.bookings) am[theB.aintCustomerID]++; return am;
}

std::map<int,int> bookingsPerStaff(const Storage &theStorage) {
    std::map<int,int> am; for (const auto &theB : theStorage.bookings) am[theB.aintStaffID]++; return am;
}

std::vector<Tour> toursInMonthYear(const Storage &theStorage, int theIntMonth, int theIntYear) {
    std::vector<Tour> avOut;
    for (const auto &theT : theStorage.tours) {
        if (theT.astrStartDate.size()!=8) continue;
        try { int aintM = std::stoi(theT.astrStartDate.substr(2,2)); int aintY = std::stoi(theT.astrStartDate.substr(4,4)); if (aintM==theIntMonth && aintY==theIntYear) avOut.push_back(theT); } catch(...) { continue; }
    }
    return avOut;
}

std::map<std::string,int> bookingsByStatus(const Storage &theStorage) {
    std::map<std::string,int> am;
    for (const auto &theB : theStorage.bookings) am[theB.astrStatus]++;
    return am;
}
