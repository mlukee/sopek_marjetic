#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_PETALS = 1e7 + 1; // Maksimalno število cvetnih listov + 1 za obseg

// Funkcija za izračun največjega skupnega delitelja (GCD)
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Struktura za segmentno drevo, ki hrani GCD vrednosti
struct SegmentTree {
    int size; // Velikost drevesa
    vector<int> tree; // Vektor za shranjevanje GCD vrednosti
    map<int, int> counts; // Map za štetje pojavitev posameznih številk

    SegmentTree() {
        size = 1;
        while (size < MAX_PETALS) size *= 2; // Poveča size na najbližjo potenco dve, ki je večja od MAX_PETALS
        tree.assign(2 * size, 0); // Inicializacija drevesa z ničlami
    }

    // Funkcija za posodobitev drevesa
    void update(int nodeIndex, int leftBound, int rightBound, int idx, int val) {
        if (rightBound - leftBound == 1) {
            // Posodobitev listov drevesa
            tree[nodeIndex] = (counts[idx] > 0 ? idx : 0);
            return;
        }
        int mid = (leftBound + rightBound) / 2; // Sredina segmenta
        if (idx < mid) {
            update(2 * nodeIndex + 1, leftBound, mid, idx, val);
        } else {
            update(2 * nodeIndex + 2, mid, rightBound, idx, val);
        }
        // Posodobi trenutno vozlišče z GCD vrednostjo njegovih vozlišč
        tree[nodeIndex] = gcd(tree[2 * nodeIndex + 1], tree[2 * nodeIndex + 2]);
    }

    // Funkcija za dodajanje ali odstranjevanje cvetnih listov
    void modify(int idx, int val) {
        counts[idx] += val; // Dodaj ali odstrani število cvetnih listov
        update(0, 0, size, idx, val); // Posodobi segmentno drevo
    }

    int query() {
        return tree[0]; // Vrne koren, ki vsebuje GCD celotnega območja
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./program input_file" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    int numOperations; // Number of operations
    inFile >> numOperations;

    SegmentTree st;

    while (numOperations--) {
        char operation; // Operation: '+' or '-'
        int petals; // Number of petals
        inFile >> operation >> petals;

        if (operation == '+') {
            st.modify(petals, 1); // Add petals
        } else if (operation == '-') {
            st.modify(petals, -1); // Remove petals
        }

        int result = st.query(); // Get current GCD
        std::cout << (result == 0 ? 1 : result) << endl; // Output result, if the tree is empty, output 1
    }

    inFile.close(); // Close input file
    return 0;
}