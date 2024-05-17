#include <iostream>
#include <fstream>
#include <vector>
#include <numeric> // for std::gcd
#include <algorithm> // for std::find

int calculateGCD(const std::vector<int>& numbers) {
    if (numbers.empty()) return 0;
    int result = numbers[0];
    for (int num : numbers) {
        result = std::gcd(result, num);
    }
    return result;
}

void processGCDFileBruteForce(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Failed to open file: " << inputFile << " or " << outputFile << std::endl;
        return;
    }

    int q;
    inFile >> q;
    std::vector<int> numbers;

    for (int i = 0; i < q; i++) {
        char operation;
        int n;
        inFile >> operation >> n;

        if (operation == '+') {
            numbers.push_back(n);
        } else if (operation == '-') {
            auto it = std::find(numbers.begin(), numbers.end(), n);
            if (it != numbers.end()) {
                numbers.erase(it);
            }
        }

        // Brute force recalculating the GCD after each operation
        int currentGCD = calculateGCD(numbers);
        outFile << (currentGCD == 0 ? 1 : currentGCD) << std::endl;
    }

    inFile.close();
    outFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <inputFile> <outputFile>" << std::endl;
        return 1; // Return non-zero value to indicate error
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    processGCDFileBruteForce(inputFile, outputFile);
    return 0;
}
