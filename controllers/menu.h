#pragma once
#include "storage.h"

void runMenu(Storage &theStorage);

// expose date helpers for tests
int parseDateToInt(const std::string &theStrDate);
int todayDateInt();

// Persistence helpers
bool loadStorageFromFile(Storage &theStorage, const std::string &theFilePath);
bool saveStorageToFile(const Storage &theStorage, const std::string &theFilePath);
