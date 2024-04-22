#include <iostream>
#include <fstream>
#include <map>
#include <vector>

// Funkcija za izračun GCD dveh števil
int gcd(int a, int b) {
    while(b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Funkcija za izračun GCD za vse marjetice v šopku
int calculateGCDofBouquet(const std::map<int, int>& bouquet) {
    // Preveri, če je šopek prazen
    bool isBouquetEmpty = true;
    for (const auto& flower : bouquet) {
        if (flower.second > 0) { // Če je vsaj ena cvetlica prisotna v šopku
            isBouquetEmpty = false;
            break;
        }
    }

    if (isBouquetEmpty) {
        return 1; // GCD je 1, če je šopek prazen
    }

    int currentGCD = 0;
    for (const auto& flower : bouquet) {
        if (flower.second > 0) { // Če je cvetlica prisotna v šopku
            if (currentGCD == 0)
                currentGCD = flower.first;
            else
                currentGCD = gcd(currentGCD, flower.first);
        }
    }
    return currentGCD;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file: " << argv[1] << std::endl;
        return 1;
    }

    std::ifstream solutionFile(argv[2]);
    if (!solutionFile.is_open()) {
        std::cerr << "Could not open the solution file: " << argv[2] << std::endl;
        return 1;
    }

    int q, n;
    char operation;
    std::map<int, int> bouquet; // Key: število cvetnih lističev, Value: število takih marjetic v šopku

    std::vector<int> programOutput;


    inputFile >> q;
    while (q--) {
        inputFile >> operation >> n;
        if (operation == '+') {
            bouquet[n]++; // Dodaj marjetico
        } else if (operation == '-') {
            bouquet[n]--; // Odstrani marjetico
        }

        int currentGCD = calculateGCDofBouquet(bouquet);
        programOutput.push_back(currentGCD);
    }

    bool isCorrect = true;
    int expectedValue;
    size_t index = 0;
    while (solutionFile >> expectedValue) {
        // Print results
        // std::cout << "Expected: " << expectedValue << ", got: " << programOutput[index] << std::endl;


        if (index >= programOutput.size() || programOutput[index] != expectedValue) {
            isCorrect = false;
            break;
        }
        index++;
    }

    // Preverimo tudi, ali imamo več rezultatov, kot je pričakovano
    if (index != programOutput.size()) {
        isCorrect = false;
    }

    if (isCorrect) {
        std::cout << "Resitev je pravilna." << std::endl;
    } else {
        std::cout << "Resitev se ne ujema s prisakovanimi rezultati." << std::endl;
    }

    return 0;
}

// g++ main.cpp -o out