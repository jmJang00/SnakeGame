#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_

#include "SnakeMap.h"
#include "constant.h"
#include <cstdlib>
#include <vector>
using namespace std;

class GameManager
{
public:
    GameManager(SnakeMap &m, Point& p);
    void randomItemGenerate();
    void randomGateGenerate();
    void gameStatusChange();
    void gameScoreChange();

    Point& snake;    // temporary
    SnakeMap& map;
    vector<Point> poisonItems;
    vector<Point> growthItems;
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