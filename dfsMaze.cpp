#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

constexpr int MAZE_WIDTH = 21;
constexpr int MAZE_HEIGHT = 21;

enum class MazeCell {
    Obstacle,
    OpenPath
};

void exploreMaze(int posX, int posY, std::vector<std::vector<MazeCell>>& labyrinth) {
    const int moveX[] = { 1, 0, -1, 0 };
    const int moveY[] = { 0, 1, 0, -1 };

    int directions[] = { 0, 1, 2, 3 };
    for (int i = 0; i < 4; ++i) {
        int randIndex = rand() % 4;
        std::swap(directions[i], directions[randIndex]);
    }

    for (int i = 0; i < 4; ++i) {
        int nextX = posX + moveX[directions[i]] * 2;
        int nextY = posY + moveY[directions[i]] * 2;
        if (nextX >= 0 && nextX < MAZE_WIDTH && nextY >= 0 && nextY < MAZE_HEIGHT && labyrinth[nextY][nextX] == MazeCell::Obstacle) {
            labyrinth[posY + moveY[directions[i]]][posX + moveX[directions[i]]] = MazeCell::OpenPath;
            labyrinth[nextY][nextX] = MazeCell::OpenPath;
            exploreMaze(nextX, nextY, labyrinth);
        }
    }
}

std::vector<std::vector<MazeCell>> createMaze(int width, int height) {
    std::vector<std::vector<MazeCell>> labyrinth(height, std::vector<MazeCell>(width, MazeCell::Obstacle));

    labyrinth[0][1] = MazeCell::OpenPath;
    labyrinth[height - 1][width - 2] = MazeCell::OpenPath;

    srand(static_cast<unsigned>(time(nullptr)));
    exploreMaze(1, 1, labyrinth);

    return labyrinth;
}

void displayMaze(const std::vector<std::vector<MazeCell>>& labyrinth) {
    for (const auto& row : labyrinth) {
        for (const auto& cell : row) {
            std::cout << (cell == MazeCell::Obstacle ? '*' : ' ');
        }
        std::cout << '\n';
    }
}

int main() {
    auto labyrinth = createMaze(MAZE_WIDTH, MAZE_HEIGHT);
    displayMaze(labyrinth);

    std::cin.get(); // Replacing system("pause") for portability
    return 0;
}
