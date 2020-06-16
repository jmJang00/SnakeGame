#ifndef _EVENT_CONTROL_
#define _EVENT_CONTROL_
#include "SnakeMap.h"

class EventControl
{
public:
    bool hitsWall;
    bool hitsPoisonItem;
    bool hitsGrowthItem;
    bool hitsGate;
    bool gameOver;
    bool winsGame;

    EventControl() {
        hitsWall = false;
        hitsPoisonItem = false;
        hitsGrowthItem = false;
        hitsGate = false;
        gameOver = false;
        winsGame = false;
    }

    bool isGameOver() {
        if (hitsWall || gameOver)
           return false;
        else
           return true;
    }
};

#endif