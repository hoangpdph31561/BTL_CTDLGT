#include <iostream>
#include "controllers/menu.h"
#include "controllers/storage.h"

int main() {
    Storage myStorage;
    runMenu(myStorage);
    std::cout << "Exiting...\n";
    return 0;
}