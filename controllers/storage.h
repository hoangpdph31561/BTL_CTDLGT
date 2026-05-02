#pragma once

#include <vector>
#include <string>
#include <map>
#include "../models/Tour.h"
#include "../models/Customer.h"
#include "../models/Staff.h"
#include "../models/Booking.h"

struct Storage {
    std::vector<Tour> tours;
    std::vector<Customer> customers;
    std::vector<Staff> staffs;
    std::vector<Booking> bookings;

    int myIntNextTourID = 1;
    int myIntNextCustomerID = 1;
    int myIntNextStaffID = 1;
    int myIntNextBookingID = 1;

    bool myBoolSampleDataGenerated = false; // flag: sample data generated once
};

// helpers
int addTour(Storage &theStorage, const Tour &theTour);
int addCustomer(Storage &theStorage, const Customer &theCustomer);
int addStaff(Storage &theStorage, const Staff &theStaff);
int addBooking(Storage &theStorage, const Booking &theBooking);

bool hasBookingsForTour(const Storage &theStorage, int aintTourID);
bool hasBookingsForCustomer(const Storage &theStorage, int aintCustomerID);
bool hasBookingsForStaff(const Storage &theStorage, int aintStaffID);

void listToursForSelection(const Storage &theStorage);
void listCustomersForSelection(const Storage &theStorage);
void listStaffForSelection(const Storage &theStorage);

// lookup
Tour* findTourByID(Storage &theStorage, int aintTourID);
Customer* findCustomerByID(Storage &theStorage, int aintCustomerID);
Staff* findStaffByID(Storage &theStorage, int aintStaffID);
Booking* findBookingByID(Storage &theStorage, int aintBookingID);

// remove
bool removeTour(Storage &theStorage, int aintTourID);
bool removeCustomer(Storage &theStorage, int aintCustomerID);
bool removeStaff(Storage &theStorage, int aintStaffID);
bool removeBooking(Storage &theStorage, int aintBookingID);

// UI helpers
bool generateSampleDataOnce(Storage &theStorage); // returns true if generated now, false if already generated

// Persistence: save entire storage to a plain-text file (simple human-readable format)
bool saveStorageToFile(const Storage &theStorage, const std::string &theFilePath);

// Load storage from a text file produced by saveStorageToFile
bool loadStorageFromFile(Storage &theStorage, const std::string &theFilePath);

// Sorting helpers
std::vector<Tour> getToursSortedByPrice(const Storage &theStorage, bool theBoolDesc=false);
std::vector<Tour> getToursSortedByStartDate(const Storage &theStorage, bool theBoolDesc=false);
std::vector<Customer> getCustomersSortedByName(const Storage &theStorage, bool theBoolDesc=false);
std::vector<Booking> getBookingsSortedByDate(const Storage &theStorage, bool theBoolDesc=false);

// Max / Min helpers
const Tour* getTourWithMaxPrice(const Storage &theStorage);
const Tour* getTourWithMinPrice(const Storage &theStorage);
const Tour* getTourWithMaxCapacity(const Storage &theStorage);
const Booking* getBookingWithMaxTotal(const Storage &theStorage);

// Aggregate helpers (totals / averages / counts)
double totalRevenue(const Storage &theStorage);
double averageRevenuePerBooking(const Storage &theStorage);
int countTours(const Storage &theStorage);
int countCustomers(const Storage &theStorage);
int totalGuestsBooked(const Storage &theStorage);

// Statistics (by conditions)
#include <map>
std::map<int,double> revenuePerTour(const Storage &theStorage);
std::map<int,int> bookingsPerCustomer(const Storage &theStorage);
std::map<int,int> bookingsPerStaff(const Storage &theStorage);
std::vector<Tour> toursInMonthYear(const Storage &theStorage, int theIntMonth, int theIntYear);
std::map<std::string,int> bookingsByStatus(const Storage &theStorage);
