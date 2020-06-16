#ifndef _EVENT_CONTROL_
#define _EVENT_CONTROL_
#include "SnakeMap.h"

class EventControl
{
public:
    bool hitsPoisonItem;
    bool hitsGrowthItem;
    bool hitsGate;
    bool gameOver;

    EventControl() {
        hitsPoisonItem = false;
        hitsGrowthItem = false;
        hitsGate = false;
        gameOver = false;
    }

    bool isGameOver() {
        if (gameOver)
           return false;
        else
           return true;
    }
};

#endif