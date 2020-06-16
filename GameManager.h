#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include "SnakeMap.h"
#include "constant.h"
#include <cstdlib>
#include <vector>
#include <list>
using namespace std;

class GameManager
{
public:
    GameManager(SnakeMap &m, Point& p);
    void randomItemGenerate();
    void randomGateGenerate();
    void itemStatusChange();
    void gameScoreChange();

    Point& snake;    // temporary
    SnakeMap& map;
    list<Item> poisonItems;
    list<Item> growthItems;
    vector<Point> wall;
    // vector<Point> snake;
    vector<Point> emptySpace;
    unsigned int frame;
    double seconds;

    // record
    unsigned int maxLengthRecord;
    unsigned int growthItemRecord;
    unsigned int poisonItemRecord;
    unsigned int gateUsageRecord;
    
    Point gates[2];
};

#endif