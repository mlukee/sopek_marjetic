#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>
#include <windows.h>
#include <psapi.h>

struct Node {
    int valueCount, gcdValue;
};

std::vector<Node> segmentTree(40000016);

int computeGCD(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int updateSegmentTree(int nodeIndex, int updateIndex, int segmentStart, int segmentEnd, int deltaValue) {
    if (updateIndex < segmentStart || updateIndex >= segmentEnd) return segmentTree[nodeIndex].gcdValue;
    if (segmentStart + 1 == segmentEnd) {
        segmentTree[nodeIndex].valueCount += deltaValue;
        segmentTree[nodeIndex].gcdValue = segmentTree[nodeIndex].valueCount > 0 ? updateIndex : 0;
        return segmentTree[nodeIndex].gcdValue;
    }
    int mid = (segmentStart + segmentEnd) / 2;
    int leftGCD = updateSegmentTree(2 * nodeIndex, updateIndex, segmentStart, mid, deltaValue);
    int rightGCD = updateSegmentTree(2 * nodeIndex + 1, updateIndex, mid, segmentEnd, deltaValue);
    int combinedGCD = computeGCD(leftGCD, rightGCD);
    segmentTree[nodeIndex].gcdValue = combinedGCD;
    return combinedGCD;
}

void processFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    std::ofstream out(outputFile);
    if (!in.is_open() || !out.is_open()) {
        std::cerr << "Failed to open " << inputFile << " or " << outputFile << std::endl;
        return;
    }

    int numOperations, index;
    char operation;
    in >> numOperations;

    for (int i = 0; i < numOperations; i++) {
        in >> operation >> index;
        int result = updateSegmentTree(1, index, 0, 10000002, operation == '+' ? 1 : -1);
        out << (result ? result : 1) << std::endl;
    }

    in.close();
    out.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    processFile(inputFile, outputFile);
    return 0;
}
