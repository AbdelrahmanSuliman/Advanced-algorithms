#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& pair) const {
        return std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1);
    }
};

static int maze[15][15] = {
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
       {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
       {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
       {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
       {0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
       {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
       {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
       {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
       {0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0},
       {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
       {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

bool BFS(std::pair<int, int> start, std::pair<int, int> end, std::vector<std::pair<int, int>>& path) {
    std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // Right, Down, Left, Up
    std::queue<std::pair<int, int>> queue;
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, pair_hash> parent;
    std::unordered_map<std::pair<int, int>, bool, pair_hash> visited;

    queue.push(start);
    visited[start] = true;
    parent[start] = start;

    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();

        if (current == end) {
            path.clear();
            while (current != start) {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return true;
        }

        for (auto& direction : directions) {
            std::pair<int, int> next_cell = { current.first + direction.first, current.second + direction.second };

            if (0 <= next_cell.first && next_cell.first < 15 &&
                0 <= next_cell.second && next_cell.second < 15 &&
                maze[next_cell.first][next_cell.second] == 1 &&  /
                !visited[next_cell])
            {
                queue.push(next_cell);
                visited[next_cell] = true;
                parent[next_cell] = current;
            }
        }
    }
    return false;
}

int main() {
    std::pair<int, int> start = { 13, 0 };  
    std::pair<int, int> end = { 1, 14 };    
    std::vector<std::pair<int, int>> path;

    if (BFS(start, end, path)) {
        std::cout << "Path found:\n";
        for (auto& p : path) {
            std::cout << "(" << p.first << ", " << p.second << ") ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "No path found.\n";
    }

    return 0;
}
