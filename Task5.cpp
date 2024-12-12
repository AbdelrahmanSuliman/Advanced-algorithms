#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib> 
#include <ctime>
#include <chrono>

void light_dark(std::vector<std::string> disks) {
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
        std::cout << disks[i] << " ";
    }

    std::cout << std::endl << counter;
}


int main() {

    int n = 3;

    std::vector<std::string> disks;

    for (int i = 0; i < 3;i++) {
        disks.push_back("dark");
        disks.push_back("light");
    }
    light_dark(disks);

}
