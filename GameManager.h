#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include "SnakeMap.h"
#include "Snake.h"
#include "constant.h"
#include <cstdlib>
#include <vector>
#include <list>
using namespace std;

class GameManager
{
public:
    GameManager(SnakeMap &m, Snake& s);
    void randomItemGenerate();
    void randomGateGenerate();
    void itemStatusChange();
    void gameStatusChange();

    Snake& snake;
    SnakeMap& map;
    list<Item> poisonItems;
    list<Item> growthItems;
    vector<Point> wall;
    vector<Point> emptySpace;
    Point gates[2];
    unsigned int frame;
    double seconds;

    // record
    unsigned int maxLengthRecord;
    unsigned int growthItemRecord;
    unsigned int poisonItemRecord;
    unsigned int gateUsageRecord;
};

#endif