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

    Item newItem;
    int idx = 0;
    int lifespan = 0;

    do {
        idx = rand() % emptySpace.size();
        lifespan = rand() % 20 + 30;
        newItem = emptySpace[idx];
        newItem.lifespan = lifespan;
    } while(newItem == snake);

    if (rand() % 2) {
        map[newItem] = GROWTH_ITEM;
        growthItems.push_back(Item(newItem));
    }
    else {
        newItem.lifespan = newItem.lifespan + 50;
        map[newItem] = POISON_ITEM;
        poisonItems.push_back(Item(newItem));
    }
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


void GameManager::itemStatusChange() {
    for (auto it=poisonItems.begin(); it != poisonItems.end(); it++) {
        it->lifespan--;
        if (it->lifespan == 0) {
            map.mat[it->row][it->col] = EMPTY_SPACE;
            emptySpace.push_back(*it);
            it = poisonItems.erase(it);
        }
    }
    for (auto it=growthItems.begin(); it != growthItems.end(); it++) {
        it->lifespan--;
        if (it->lifespan == 0) {
            map.mat[it->row][it->col] = EMPTY_SPACE;
            emptySpace.push_back(*it);
            it = growthItems.erase(it);
        }
    }
}
