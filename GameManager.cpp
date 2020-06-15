#include "GameManager.h"

GameManager::GameManager(SnakeMap &m, Point& p):
map(m), snake(p), frame(0), seconds(0) {    // Point& p temporary
    for (int i=0; i<map.row; i++) {
        for (int j=0; j<map.col; j++) {
            if (map.mat[i][j] == EMPTY_SPACE)
                emptySpace.push_back(Point(i, j));
            else if (map.mat[i][j] == WALL)
                wall.push_back(Point(i, j));
        }
    }
    maxLengthRecord = 1;
    growthItemRecord = 0;
    poisonItemRecord = 0;
    gateUsageRecord = 0;

    seconds = 0;
}

void GameManager::randomItemGenerate() {
    if (frame % 20 != 0)
        return;

    Point newItem;
    int idx = 0;

    do {
        idx = rand() % emptySpace.size();
        newItem = emptySpace[idx];
    } while(newItem == snake);

    if (rand() % 2)
        map.mat[newItem.row][newItem.col] = GROWTH_ITEM;
    else
        map.mat[newItem.row][newItem.col] = POISON_ITEM;
    emptySpace.erase(emptySpace.begin() + idx);
}

void GameManager::randomGateGenerate() {
    for (int i=0; i<2; i++) {
        int idx = rand() % wall.size();
        gates[0] = wall[idx];
        map[gates[0]] = GATE;
        wall.erase(wall.begin() + idx);
    }
}