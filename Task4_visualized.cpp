#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

const int NUM_DISKS = 3;
const int ROD_WIDTH = 10;
const int ROD_HEIGHT = 200;
const int BASE_HEIGHT = 20;
const int DISK_HEIGHT = 20;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 400;

sf::Vector2f rodPositions[3] = {
    {200, 100},
    {400, 100},
    {600, 100}
};

struct Disk {
    sf::RectangleShape shape;
    int size;
};


std::vector<Disk> rods[3];

void initializeDisks(int numDisks) {
    for (int i = 0; i < 3; i++) {
        rods[i].clear();
    }

    for (int i = 0; i < numDisks; ++i) {
        Disk disk;
        disk.size = numDisks - i;
        disk.shape.setSize(sf::Vector2f(50 + disk.size * 20, DISK_HEIGHT));
        disk.shape.setFillColor(sf::Color::Green);
        disk.shape.setOrigin(disk.shape.getSize().x / 2, disk.shape.getSize().y / 2);
        rods[0].push_back(disk);
    }
}

void drawScene(sf::RenderWindow& window) {
    window.clear(sf::Color::White);


    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape rod(sf::Vector2f(ROD_WIDTH, ROD_HEIGHT));
        rod.setFillColor(sf::Color::Black);
        rod.setOrigin(ROD_WIDTH / 2, ROD_HEIGHT / 2);
        rod.setPosition(rodPositions[i]);
        window.draw(rod);
    }


    for (int i = 0; i < 3; ++i) {
        int diskCount = rods[i].size();
        for (int j = 0; j < diskCount; ++j) {
            rods[i][j].shape.setPosition(rodPositions[i].x, rodPositions[i].y + ROD_HEIGHT / 2 - j * (DISK_HEIGHT + 5));
            window.draw(rods[i][j].shape);
        }
    }

    window.display();
}

void moveDisk(int from, int to) {
    if (rods[from].empty()) return;

    Disk disk = rods[from].back();
    rods[from].pop_back();
    rods[to].push_back(disk);
}

void restrictedTowerOfHanoi(int n, int src, int aux, int dst, sf::RenderWindow& window) {
    if (n == 0) return;

    restrictedTowerOfHanoi(n - 1, src, aux, dst, window);

    moveDisk(src, aux);
    drawScene(window);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    restrictedTowerOfHanoi(n - 1, dst, aux, src, window);

    moveDisk(aux, dst);
    drawScene(window);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    restrictedTowerOfHanoi(n - 1, src, aux, dst, window);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Restricted Tower of Hanoi");

    initializeDisks(NUM_DISKS);
    drawScene(window);

    restrictedTowerOfHanoi(NUM_DISKS, 0, 1, 2, window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}

