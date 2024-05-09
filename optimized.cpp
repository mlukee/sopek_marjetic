#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>
#include <windows.h>
#include <psapi.h>

struct Node {
    size_t valueCount, gcdValue;
};

std::vector<Node> segmentTree(40000016); // Adjust the size based on the maximum possible input constraints

size_t computeGCD(size_t a, size_t b) {
    while (b != 0) {
        size_t temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

size_t updateSegmentTree(size_t nodeIndex, size_t updateIndex, size_t segmentStart, size_t segmentEnd, size_t deltaValue) {
    if (updateIndex < segmentStart || updateIndex >= segmentEnd) return segmentTree[nodeIndex].gcdValue;
    if (segmentStart + 1 == segmentEnd) {
        segmentTree[nodeIndex].valueCount += deltaValue;
        segmentTree[nodeIndex].gcdValue = segmentTree[nodeIndex].valueCount > 0 ? updateIndex : 0;
        return segmentTree[nodeIndex].gcdValue;
    }
    size_t mid = (segmentStart + segmentEnd) / 2;
    size_t leftGCD = updateSegmentTree(2 * nodeIndex, updateIndex, segmentStart, mid, deltaValue);
    // std::cout  << "updateSegmentTree(" << 2 * nodeIndex + 1 << ", " << updateIndex << ", " << mid << ", " << segmentEnd << ", " << deltaValue << ")\n";
    size_t rightGCD = updateSegmentTree(2 * nodeIndex + 1, updateIndex, mid, segmentEnd, deltaValue);
    // std::cout << "updateSegmentTree(" << 2 * nodeIndex + 1 << ", " << updateIndex << ", " << mid << ", " << segmentEnd << ", " << deltaValue << ")\n";
    size_t combinedGCD = computeGCD(leftGCD, rightGCD);
    segmentTree[nodeIndex].gcdValue = combinedGCD;
    return combinedGCD;
}

void processFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    std::ifstream out(outputFile);
    if (!in.is_open() || !out.is_open()) {
        std::cerr << "Failed to open " << inputFile << " or " << outputFile << std::endl;
        return;
    }

    // Clear Segment Tree
    for (size_t i = 0; i < segmentTree.size(); i++) {
        segmentTree[i].valueCount = 0;
        segmentTree[i].gcdValue = 0;
    }

    size_t numOperations, index;
    char operation;
    in >> numOperations;

    bool correct = true;
    size_t expectedResult, actualResult;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numOperations; i++) {
        in >> operation >> index;
        actualResult = updateSegmentTree(1, index, 0, 10000002, operation == '+' ? 1 : -1);
        out >> expectedResult;
        actualResult = actualResult ? actualResult : 1;
        if (actualResult != expectedResult) {
            // std::cout << "Mismatch at operation " << i + 1 << ": Expected " << expectedResult << ", got " << actualResult << std::endl;
            correct = false;
            // break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    if (correct) {
        std::cout << inputFile << ": Correct, Time: " << std::fixed << std::setprecision(6) << elapsed.count() << "s\n";
    } else {
        std::cout << inputFile << ": Incorrect\n";
    }

    in.close();
    out.close();
}



int main() {
    for (size_t i = 1; i <= 14; ++i) {
        if (i == 7 || i == 11) continue;  // Skip files 7 and 11 as per your requirement
        std::string inputFile = "test_cases\\marjetice" + (i < 10 ? "0" + std::to_string(i) : std::to_string(i)) + ".in";
        std::string outputFile = "test_cases\\marjetice" + (i < 10 ? "0" + std::to_string(i) : std::to_string(i)) + ".out";
        processFile(inputFile, outputFile);
    }
    return 0;
}
