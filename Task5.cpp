#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<string> disks;

    for (int i = 0; i < N; i++) {
        disks.push_back("dark");
        disks.push_back("light");
    }

    int size = disks.size();

    int counter = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (disks[j] == "dark" && disks[j + 1] == "light") {
                std::swap(disks[j], disks[j + 1]);
                counter++;
            }
        }
    }

    for (int i = 0; i < disks.size(); i++) {
        cout << disks[i] << " ";
    }

    std::cout << std::endl << counter;
}
