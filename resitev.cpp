#include <iostream>
#include <fstream>
#include <vector>

struct Node {
    int valueCount, gcdValue;
};

std::vector<Node> segmentTree(40000016); // Size may need adjustment based on constraints

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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file: " << argv[1] << std::endl;
        return 1;
    }

    int numOperations, index;
    char operation;
    inputFile >> numOperations;

    for (int i = 0; i < numOperations; i++) {
        inputFile >> operation >> index;
        int gcdResult = updateSegmentTree(1, index, 0, 10000002, operation == '+' ? 1 : -1);
        std::cout << (gcdResult ? gcdResult : 1) << std::endl;
    }

    inputFile.close();
    return 0;
}
