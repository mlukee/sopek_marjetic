#include <iostream>
#include <fstream>
#include <map>

int gcd(int a, int b) {
    while (b != 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}
// C:\POT\sopek_marjetic\cmake-build-debug\sopek_marjetic.exe ./test.txt | Out-File out.txt
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 2;
    }

    int q;
    inFile >> q;

    std::map<int, int> petalCount;
    int currentGCD = 0;

    for (int i = 0; i < q; i++) {
        char operation;
        int n;
        inFile >> operation >> n;

        if (operation == '+') {
            if (petalCount[n] == 0) {
                if (currentGCD == 0) {
                    currentGCD = n;
                } else {
                    currentGCD = gcd(currentGCD, n);
                }
            }
            petalCount[n]++;
        } else if (operation == '-') {
            if (--petalCount[n] == 0) {
                petalCount.erase(n);

                if (petalCount.empty()) {
                    currentGCD = 0;
                } else {
                    auto it = petalCount.begin();
                    currentGCD = it->first;
                    for (++it; it != petalCount.end(); ++it) {
                        currentGCD = gcd(currentGCD, it->first);
                        if (currentGCD == 1) break;
                    }
                }
            }
        }

        if (currentGCD == 0 || petalCount.empty()) {
            std::cout << 1 << std::endl;
        } else {
            std::cout << currentGCD << std::endl;
        }
    }

    inFile.close();
    return 0;
}
