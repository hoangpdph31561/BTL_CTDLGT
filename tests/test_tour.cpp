#include <iostream>
#include <cassert>
#include "../controllers/storage.h"

int main() {
    Storage theStorage;

    // Test 1: addTour returns ID 1
    Tour t1("Test Tour 1", 150.0, 10);
    int aintId1 = addTour(theStorage, t1);
    assert(aintId1 == 1);

    // Test 2: findTourByID
    Tour* pTour = findTourByID(theStorage, aintId1);
    assert(pTour != nullptr);
    assert(pTour->astrTourName == "Test Tour 1");

    // Test 3: add second tour -> ID increments
    Tour t2("Test Tour 2", 200.0, 5);
    int aintId2 = addTour(theStorage, t2);
    assert(aintId2 == 2);
    assert(theStorage.tours.size() == 2);

    // Test 4: remove non-existing tour
    bool removed = removeTour(theStorage, 999);
    assert(!removed);

    // Test 5: remove existing tour without bookings
    removed = removeTour(theStorage, aintId1);
    assert(removed);
    assert(findTourByID(theStorage, aintId1) == nullptr);

    // Test 6: ensure next IDs continue incrementing
    Tour t3("Test Tour 3", 300.0, 8);
    int aintId3 = addTour(theStorage, t3);
    assert(aintId3 == 3);

    std::cout << "test_tour: all tests passed\n";
    return 0;
}
