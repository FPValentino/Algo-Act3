#ifndef STOCK_NAMES_H
#define STOCK_NAMES_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int STOCK_COUNT;
string* stockNames;

string generateRandomStockName() {
    string name;
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int length = rand() % 4 + 2;
    for (int i = 0; i < length; i++) {
        name += letters[rand() % letters.size()];
    }
    return name;
}

void generateStockNames(int count) {
    STOCK_COUNT = count;
    stockNames = new string[STOCK_COUNT];
    for (int i = 0; i < STOCK_COUNT; i++) {
        stockNames[i] = generateRandomStockName();
    }
}

void cleanupStockNames() {
    delete[] stockNames;
}

#endif // STOCK_NAMES_H