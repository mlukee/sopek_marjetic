#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <iomanip>
#include <string>

int gcd(int a, int b) {
    while (b != 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

void processGCDFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ifstream expectedFile(outputFile);
    if (!inFile.is_open() || !expectedFile.is_open()) {
        std::cerr << "Failed to open file: " << inputFile << " or " << outputFile << std::endl;
        return;
    }

    int q;
    inFile >> q;

    std::map<int, int> petalCount;
    int currentGCD = 0;
    bool correct = true;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < q; i++) {
        char operation;
        int n;
        inFile >> operation >> n;

        int expectedGCD;
        expectedFile >> expectedGCD;

        if (operation == '+') {
            if (petalCount[n] == 0) {  // Only update GCD if this petal count was zero before addition
                if (currentGCD == 0) {
                    currentGCD = n;
                } else {
                    currentGCD = gcd(currentGCD, n);
                }
            }
            petalCount[n]++;
        } else if (operation == '-') {
            petalCount[n]--;
            if (petalCount[n] == 0) {  // Petal completely removed, need to recalculate GCD
                petalCount.erase(n);
                currentGCD = 0;
                for (auto& p : petalCount) {
                    if (currentGCD == 0) {
                        currentGCD = p.first;
                    } else {
                        currentGCD = gcd(currentGCD, p.first);
                        if (currentGCD == 1) break;  // Short-circuit if GCD is 1
                    }
                }
            }
        }

        int outputGCD = (currentGCD == 0 || petalCount.empty()) ? 1 : currentGCD;
        if (outputGCD != expectedGCD) {
            correct = false;
            std::cout << "Mismatch at operation " << i + 1 << ": Expected " << expectedGCD << ", got " << outputGCD << std::endl;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << inputFile << ": " << (correct ? "Correct" : "Incorrect") << ", Time: " << std::fixed << std::setprecision(6) << elapsed.count() << "s\n";

    inFile.close();
    expectedFile.close();
}



int main() {
    for (int i = 1; i <= 13; ++i) {
        if(i==7 || i==11) continue; // Skip files 7 and 11 (as per your requirement
        std::string index = (i < 10 ? "0" + std::to_string(i) : std::to_string(i));
        std::string inputFile = "test_cases\\marjetice" + index + ".in";
        std::string outputFile = "test_cases\\marjetice" + index + ".out";
        processGCDFile(inputFile, outputFile);
    }
    return 0;
}
