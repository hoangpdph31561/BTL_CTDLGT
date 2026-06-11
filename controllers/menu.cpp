#include <iostream>
#include "menu.h"
#include <string>
#include <limits>
#include <chrono>
#include <fstream>
#include <filesystem>

using namespace std;

static int readInt(const std::string &theStrPrompt) {
    int aintVal;
    while (true) {
        std::cout << theStrPrompt;
        if (std::cin >> aintVal) { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); return aintVal; }
        std::cout << "Invalid input, try again.\n";
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

static double readDouble(const std::string &theStrPrompt) {
    double adblVal;
    while (true) {
        std::cout << theStrPrompt;
        if (std::cin >> adblVal) { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); return adblVal; }
        std::cout << "Invalid input, try again.\n";
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

static std::string readLine(const std::string &theStrPrompt) {
    std::string astr;
    std::cout << theStrPrompt;
    std::getline(std::cin, astr);
    return astr;
}

// Date helpers: parse DDMMYYYY into YYYYMMDD int, return 0 on error
int parseDateToInt(const std::string &theStrDate) {
    // Expect exactly 8 digits: DDMMYYYY
    if (theStrDate.size() != 8) return 0;
    for (char c : theStrDate) if (!isdigit((unsigned char)c)) return 0;
    try {
        int aintD = std::stoi(theStrDate.substr(0,2));
        int aintM = std::stoi(theStrDate.substr(2,2));
        int aintY = std::stoi(theStrDate.substr(4,4));
        if (aintM < 1 || aintM > 12) return 0;
        if (aintD < 1 || aintD > 31) return 0;
        // convert to YYYYMMDD for easy comparison
        return aintY*10000 + aintM*100 + aintD;
    } catch(...) { return 0; }
}

int todayDateInt() {
    using namespace std::chrono;
    std::time_t t = system_clock::to_time_t(system_clock::now());
    std::tm local;
#if defined(_WIN32)
    localtime_s(&local, &t);
#else
    local = *std::localtime(&t);
#endif
    int aintY = local.tm_year + 1900;
    int aintM = local.tm_mon + 1;
    int aintD = local.tm_mday;
    return aintY*10000 + aintM*100 + aintD;
}

void listBookingsDetailed(const Storage &theStorage) {
    std::cout << "ID | TourName | CustomerName | StaffName | Qty | Total | Date | Status\n";
    for (const auto &theB : theStorage.bookings) {
        const Tour* pTour = nullptr; const Customer* pCustomer = nullptr; const Staff* pStaff = nullptr;
        for (const auto &theT : theStorage.tours) if (theT.aintTourID == theB.aintTourID) { pTour = &theT; break; }
        for (const auto &theC : theStorage.customers) if (theC.aintCustomerID == theB.aintCustomerID) { pCustomer = &theC; break; }
        for (const auto &theS : theStorage.staffs) if (theS.aintStaffID == theB.aintStaffID) { pStaff = &theS; break; }
        std::cout << theB.aintBookingID << " | " << (pTour? pTour->astrTourName : "(tour?)") << " | " << (pCustomer? pCustomer->astrCustomerName : "(cust?)") << " | " << (pStaff? pStaff->astrStaffName : "(staff?)") << " | " << theB.aintQuantity << " | " << theB.adblTotal << " | " << theB.astrBookingDate << " | " << theB.astrStatus << "\n";
    }
}

void menuTour(Storage &theStorage) {
    while (true) {
        std::cout << "\n--- Tour Menu ---\n1. List Tours\n2. Add Tour\n3. Find Tour by ID\n4. Find Tour by Name\n5. Delete Tour\n0. Back\nChoose: ";
        int aintChoice = readInt("");
        switch (aintChoice) {
            case 0: return;
            case 1: {
                if (theStorage.tours.empty()) { std::cout << "No tours available\n"; break; }
                for (const auto &theT : theStorage.tours) {
                    std::cout << "ID: " << theT.aintTourID << ", Name: " << theT.astrTourName << ", Origin: " << theT.astrOrigin << ", Destination: " << theT.astrDestination << ", Start: " << theT.astrStartDate << ", End: " << theT.astrEndDate << ", Price: " << theT.adblPrice << ", Capacity: " << theT.aintCapacity << "\n";
                }
                break;
            }
            case 2: {
                Tour theNewTour; theNewTour.astrTourName = readLine("Name: "); theNewTour.astrOrigin = readLine("Origin: "); theNewTour.astrDestination = readLine("Destination: "); theNewTour.astrStartDate = readLine("Start date (DDMMYYYY): "); theNewTour.astrEndDate = readLine("End date (DDMMYYYY): ");
                int aintStart = parseDateToInt(theNewTour.astrStartDate);
                int aintEnd = parseDateToInt(theNewTour.astrEndDate);
                int aintToday = todayDateInt();
                if (aintStart == 0 || aintEnd == 0) { std::cout << "Invalid date format. Use DDMMYYYY. Tour not added.\n"; break; }
                if (aintStart < aintToday) { std::cout << "Start date must be today or later. Tour not added.\n"; break; }
                if (aintEnd < aintStart) { std::cout << "End date must be on/after start date. Tour not added.\n"; break; }
                theNewTour.adblPrice = readDouble("Price: "); theNewTour.aintCapacity = readInt("Capacity: "); int aintID = addTour(theStorage, theNewTour); std::cout << "Added Tour ID=" << aintID << "\n"; break;
            }
            case 3: {
                int aintID = readInt("Tour ID: "); Tour* pTour = findTourByID(theStorage, aintID); if (pTour) std::cout << "ID: "<<pTour->aintTourID<<", Name: "<<pTour->astrTourName<<", Destination: "<<pTour->astrDestination<<", Start: "<<pTour->astrStartDate<<", Price: "<<pTour->adblPrice<<"\n"; else std::cout << "Not found\n"; break;
            }
            case 4: {
                std::string astrName = readLine("Name to search: "); bool aboolFound = false; for (const auto &theT : theStorage.tours) if (theT.astrTourName.find(astrName) != std::string::npos) { std::cout << "ID: " << theT.aintTourID << ", Name: " << theT.astrTourName << ", Destination: " << theT.astrDestination << ", Start: " << theT.astrStartDate << ", Price: " << theT.adblPrice << "\n"; aboolFound = true; } if (!aboolFound) std::cout << "No matches\n"; break;
            }
            case 5: {
                int aintID = readInt("Tour ID to delete: "); if (removeTour(theStorage, aintID)) std::cout << "Deleted\n"; else std::cout << "Delete blocked (maybe bookings reference it) or not found\n"; break;
            }
            default: std::cout << "Invalid choice\n"; break;
        }
    }
}

void menuCustomer(Storage &theStorage) {
    while (true) {
        std::cout << "\n--- Customer Menu ---\n1. List Customers\n2. Add Customer\n3. Find Customer by ID\n4. Delete Customer\n0. Back\nChoose: ";
        int aintChoice = readInt("");
        switch (aintChoice) {
            case 0: return;
            case 1: {
                if (theStorage.customers.empty()) { std::cout << "No customers available\n"; break; }
                for (const auto &theC : theStorage.customers) {
                    std::cout << "ID: " << theC.aintCustomerID << ", Name: " << theC.astrCustomerName << ", Phone: " << theC.astrPhone << ", Email: " << theC.astrEmail << ", Address: " << theC.astrAddress << "\n";
                }
                break;
            }
            case 2: {
                Customer theNewCustomer; theNewCustomer.astrCustomerName = readLine("Name: "); theNewCustomer.astrPhone = readLine("Phone: "); theNewCustomer.astrEmail = readLine("Email: "); theNewCustomer.astrAddress = readLine("Address: "); int aintID = addCustomer(theStorage, theNewCustomer); std::cout << "Added Customer ID="<<aintID<<"\n"; break;
            }
            case 3: {
                int aintID = readInt("Customer ID: "); Customer* pCustomer = findCustomerByID(theStorage, aintID); if (pCustomer) std::cout << "ID: "<<pCustomer->aintCustomerID<<", Name: "<<pCustomer->astrCustomerName<<", Phone: "<<pCustomer->astrPhone<<"\n"; else std::cout<<"Not found\n"; break;
            }
            case 4: {
                int aintID = readInt("Customer ID to delete: "); if (removeCustomer(theStorage, aintID)) std::cout<<"Deleted\n"; else std::cout<<"Delete blocked or not found\n"; break;
            }
            default: std::cout<<"Invalid choice\n"; break;
        }
    }
}

void menuStaff(Storage &theStorage) {
    while (true) {
        std::cout << "\n--- Staff Menu ---\n1. List Staffs\n2. Add Staff\n3. Find Staff by ID\n4. Delete Staff\n0. Back\nChoose: ";
        int aintChoice = readInt("");
        switch (aintChoice) {
            case 0: return;
            case 1: {
                if (theStorage.staffs.empty()) { std::cout << "No staff available\n"; break; }
                for (const auto &theS : theStorage.staffs) {
                    std::cout << "ID: " << theS.aintStaffID << ", Name: " << theS.astrStaffName << ", Position: " << theS.astrPosition << ", Phone: " << theS.astrPhone << ", Email: " << theS.astrEmail << "\n";
                }
                break;
            }
            case 2: {
                Staff theNewStaff; theNewStaff.astrStaffName = readLine("Name: "); theNewStaff.astrPosition = readLine("Position: "); theNewStaff.astrPhone = readLine("Phone: "); theNewStaff.astrEmail = readLine("Email: "); int aintID = addStaff(theStorage, theNewStaff); std::cout<<"Added Staff ID="<<aintID<<"\n"; break;
            }
            case 3: {
                int aintID = readInt("Staff ID: "); Staff* pStaff = findStaffByID(theStorage, aintID); if (pStaff) std::cout<<"ID: "<<pStaff->aintStaffID<<", Name: "<<pStaff->astrStaffName<<", Position: "<<pStaff->astrPosition<<"\n"; else std::cout<<"Not found\n"; break;
            }
            case 4: {
                int aintID = readInt("Staff ID to delete: "); if (removeStaff(theStorage, aintID)) std::cout<<"Deleted\n"; else std::cout<<"Delete blocked or not found\n"; break;
            }
            default: std::cout<<"Invalid choice\n"; break;
        }
    }
}

void menuBooking(Storage &theStorage) {
    while (true) {
        std::cout << "\n--- Booking Menu ---\n1. List Bookings\n2. Add Booking\n3. Delete Booking\n0. Back\nChoose: ";
        int aintChoice = readInt("");
        switch (aintChoice) {
            case 0: return;
            case 1: {
                listBookingsDetailed(theStorage);
                break;
            }
            case 2: {
                std::cout << "Select Tour:\n"; listToursForSelection(theStorage);
                int aintTourID = readInt("Tour ID: ");
                Tour* pTour = findTourByID(theStorage, aintTourID);
                if (!pTour) { std::cout << "Tour not found\n"; break; }
                int aintTStart = parseDateToInt(pTour->astrStartDate);
                int aintTEnd = parseDateToInt(pTour->astrEndDate);
                int aintToday = todayDateInt();
                if (aintTStart == 0 || aintTEnd == 0) { std::cout << "Tour has invalid start/end dates, cannot book.\n"; break; }
                if (aintToday > aintTEnd) { std::cout << "Tour already finished, cannot book.\n"; break; }
                if (aintToday > aintTStart) { std::cout << "Booking period closed (tour already started).\n"; break; }

                std::cout << "Select Customer:\n"; listCustomersForSelection(theStorage);
                int aintCustomerID = readInt("Customer ID: ");
                std::cout << "Select Staff (creator):\n"; listStaffForSelection(theStorage);
                int aintStaffID = readInt("Staff ID: ");
                int aintQuantity = readInt("Quantity: ");

                std::string astrBookingDate = readLine("Booking date (DDMMYYYY): ");
                int aintBDate = parseDateToInt(astrBookingDate);
                if (aintBDate == 0) { std::cout << "Invalid booking date format. Use DDMMYYYY.\n"; break; }
                // Require booking date to be within tour start/end range and not in the past
                if (aintBDate < aintTStart || aintBDate > aintTEnd) { std::cout << "Booking date must be between tour start and end dates (" << pTour->astrStartDate << " - " << pTour->astrEndDate << ").\n"; break; }
                if (aintBDate < aintToday) { std::cout << "Booking date cannot be in the past.\n"; break; }

                double adblTotal = (pTour? pTour->adblPrice * aintQuantity : 0.0);
                Booking theBooking(aintTourID, aintCustomerID, aintStaffID, aintQuantity, adblTotal);
                theBooking.astrBookingDate = astrBookingDate;
                theBooking.astrStatus = readLine("Status: ");
                int aintID = addBooking(theStorage, theBooking);
                std::cout << "Added Booking ID="<<aintID<<" Total="<<adblTotal<<"\n";
                break;
            }
            case 3: {
                int aintID = readInt("Booking ID to delete: ");
                if (removeBooking(theStorage, aintID)) std::cout << "Deleted\n"; else std::cout << "Not found\n";
                break;
            }
            default: std::cout << "Invalid choice\n"; break;
        }
    }
}

void menuReports(Storage &theStorage) {
    while (true) {
        std::cout << "\n--- Reports / Statistics ---\n1. List Tours sorted by price (asc)\n2. List Tours sorted by start date (asc)\n3. List Customers sorted by name\n4. List Bookings sorted by date\n5. Show tour with max price and min price\n6. Show tour with max capacity\n7. Total revenue / avg per booking / total guests\n8. Revenue per tour\n9. Bookings per customer (counts)\n10. Bookings per staff (counts)\n11. Tours in month/year\n12. Bookings by status\n13. Count tours with same origin as first\n0. Back\nChoose: ";
        int aintChoice = readInt("");
        switch (aintChoice) {
            case 0: return;
            case 1: {
                auto avTours = getToursSortedByPrice(theStorage, false);
                for (const auto &t : avTours) std::cout<<"ID:"<<t.aintTourID<<" Name:"<<t.astrTourName<<" Price:"<<t.adblPrice<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 2: {
                auto avTours = getToursSortedByStartDate(theStorage, false);
                for (const auto &t : avTours) std::cout<<"ID:"<<t.aintTourID<<" Name:"<<t.astrTourName<<" Start:"<<t.astrStartDate<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 3: {
                auto avCust = getCustomersSortedByName(theStorage, false);
                for (const auto &c : avCust) std::cout<<"ID:"<<c.aintCustomerID<<" Name:"<<c.astrCustomerName<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 4: {
                auto avB = getBookingsSortedByDate(theStorage, false);
                for (const auto &b : avB) std::cout<<"ID:"<<b.aintBookingID<<" TourID:"<<b.aintTourID<<" Date:"<<b.astrBookingDate<<" Total:"<<b.adblTotal<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 5: {
                auto ptMax = getTourWithMaxPrice(theStorage); auto ptMin = getTourWithMinPrice(theStorage);
                if (ptMax) std::cout<<"Max price: ID="<<ptMax->aintTourID<<" Name="<<ptMax->astrTourName<<" Price="<<ptMax->adblPrice<<"\n"; else std::cout<<"No tours\n";
                if (ptMin) std::cout<<"Min price: ID="<<ptMin->aintTourID<<" Name="<<ptMin->astrTourName<<" Price="<<ptMin->adblPrice<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 6: {
                auto pt = getTourWithMaxCapacity(theStorage);
                if (pt) std::cout<<"Max capacity: ID="<<pt->aintTourID<<" Name="<<pt->astrTourName<<" Cap="<<pt->aintCapacity<<"\n"; else std::cout<<"No tours\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 7: {
                double adblTotal = totalRevenue(theStorage); double adblAvg = averageRevenuePerBooking(theStorage); int aintGuests = totalGuestsBooked(theStorage);
                std::cout<<"Total revenue="<<adblTotal<<" Avg per booking="<<adblAvg<<" Total guests="<<aintGuests<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 8: {
                auto amap = revenuePerTour(theStorage);
                for (const auto &kv : amap) std::cout<<"TourID="<<kv.first<<" Revenue="<<kv.second<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 9: {
                auto amap = bookingsPerCustomer(theStorage);
                for (const auto &kv : amap) std::cout<<"CustomerID="<<kv.first<<" Count="<<kv.second<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 10: {
                auto amap = bookingsPerStaff(theStorage);
                for (const auto &kv : amap) std::cout<<"StaffID="<<kv.first<<" Count="<<kv.second<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 11: {
                int aintMonth = readInt("Month (1-12): "); int aintYear = readInt("Year (e.g. 2026): "); auto av = toursInMonthYear(theStorage, aintMonth, aintYear); for (const auto &t: av) std::cout<<"ID="<<t.aintTourID<<" Name="<<t.astrTourName<<" Start="<<t.astrStartDate<<"\n"; readLine("Press Enter to continue..."); break;
            }
            case 12: {
                auto amap = bookingsByStatus(theStorage);
                for (const auto &kv : amap) std::cout<<"Status='"<<kv.first<<"' Count="<<kv.second<<"\n";
                readLine("Press Enter to continue...");
                break;
            }
            case 13: {
                if (theStorage.tours.empty()) {
                    std::cout << "No tours available to compare.\n";
                } else {
                    std::string astrOrigin = theStorage.tours[0].astrOrigin;
                    int aintResult = countToursWithSameOriginAsFirst(theStorage);
                    
                    std::cout << "-------------------------------------------\n";
                    std::cout << "First tour: " << theStorage.tours[0].astrTourName << "\n";
                    std::cout << "Origin of first tour: " << astrOrigin << "\n";
                    std::cout << "Total tours starting from " << astrOrigin << ": " << aintResult << "\n";
                    std::cout << "-------------------------------------------\n";
                }
                readLine("Press Enter to continue...");
                break;
            }
            default: std::cout<<"Invalid choice\n"; break;
        }
    }
}

// Update runMenu to add Reports option
void runMenu(Storage &theStorage) {
    while (true) {
        std::cout << "\n=== Main Menu ===\n1. Tours\n2. Customers\n3. Staff\n4. Bookings\n5. Generate Sample Data\n6. Save Storage to File\n7. Load Storage from File\n8. Reports / Statistics\n0. Exit\nChoose: ";
        int choice = readInt("");
        switch (choice) {
            case 0: return;
            case 1: menuTour(theStorage); break;
            case 2: menuCustomer(theStorage); break;
            case 3: menuStaff(theStorage); break;
            case 4: menuBooking(theStorage); break;
            case 5: {
                if (generateSampleDataOnce(theStorage)) std::cout<<"Sample data generated\n"; else std::cout<<"Sample data already generated, cannot generate again\n";
                break;
            }
            case 6: {
                std::string path = readLine("File path to save (default: storage_dump.txt in project folder): ");
                if (path.empty()) {
                    // default to current working directory (should be project root / location of main.exe when run from VSCode)
                    std::filesystem::path p = std::filesystem::current_path();
                    p /= "storage_dump.txt";
                    path = p.string();
                }
                // If file exists, ask for confirmation before overwrite
                std::ifstream ifs(path);
                if (ifs.is_open()) {
                    ifs.close();
                    std::string yn = readLine("File exists. Overwrite? (Y/N): ");
                    if (yn.empty() || (yn[0] != 'Y' && yn[0] != 'y')) {
                        std::cout << "Save cancelled.\n";
                        break;
                    }
                }
                bool ok = saveStorageToFile(theStorage, path);
                if (ok) std::cout << "Saved storage to " << path << " (existing file was overwritten if present)\n";
                else std::cout << "Failed to save storage to " << path << "\n";
                break;
            }
            case 7: {
                std::string path = readLine("File path to load (default: storage_dump.txt in project folder): ");
                if (path.empty()) {
                    std::filesystem::path p = std::filesystem::current_path();
                    p /= "storage_dump.txt";
                    path = p.string();
                }
                bool ok = loadStorageFromFile(theStorage, path);
                if (ok) std::cout << "Loaded storage from " << path << "\n";
                else std::cout << "Failed to load storage from " << path << "\n";
                break;
            }
            case 8: menuReports(theStorage); break;
            default: std::cout << "Invalid choice\n"; break;
        }
    }
}
