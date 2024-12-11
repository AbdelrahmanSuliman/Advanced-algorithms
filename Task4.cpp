#include <iostream>

void restricted_tower_of_hanoi(int n, char src, char aux, char dst) {
    if (n == 0) return;

    restricted_tower_of_hanoi(n - 1, src, aux, dst);

    std::cout << "Disk " << n << " moved from " << src << " to " << aux << std::endl;

    restricted_tower_of_hanoi(n - 1, dst, aux, src);

    std::cout << "Disk " << n << " moved from " << aux << " to " << dst << std::endl;

    restricted_tower_of_hanoi(n - 1, src, aux, dst);
}

int main() {
    int n = 3;
    restricted_tower_of_hanoi(n, 'A', 'B', 'C');
    return 0;
}
