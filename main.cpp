#include <ncurses.h>
#include <iostream>
// #include "snake.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include "constant.h"
#include "SnakeMap.h"
#include "EventControl.h"
#include "GameManager.h"
// screen block code

using namespace std;
using std::vector;

int main()
{
    int row, col;

    // configure
    initscr();
    getmaxyx(stdscr, row, col);
    noecho();
    start_color();
    srand(time(NULL));
    keypad(stdscr, TRUE);

    mvprintw((row-1)/2 - 1, (col-22)/2 - 1, "press any key to start");
    refresh();
    getch();
    nodelay(stdscr, TRUE);

    int mainWinR = row;
    int mainWinC = col / 2;
    Point mainWinLoc(0, 0);

    int scoreWinR = row / 2;
    int scoreWinC = col - mainWinC;
    Point scoreWinLoc(0, mainWinC);

    int missionWinR = row - scoreWinR;
    int missionWinC = scoreWinC;
    Point missionWinLoc(scoreWinR, mainWinC);

    WINDOW* mainWindow;
    WINDOW* scoreWindow;
    WINDOW* missionWindow;
    mainWindow = newwin(mainWinR, mainWinC, mainWinLoc.row, mainWinLoc.col);
    scoreWindow = newwin(scoreWinR, scoreWinC, scoreWinLoc.row, scoreWinLoc.col);
    missionWindow = newwin(missionWinR, missionWinC, missionWinLoc.row, missionWinLoc.col);
    wborder(mainWindow, '|', '|', '-','-','+','+','+','+');
    wborder(missionWindow, '|', '|', '-','-','+','+','+','+');
    wborder(scoreWindow, '|', '|', '-','-','+','+','+','+');
    SnakeMap map(mainWinR, mainWinC, mainWindow);

    
    map.eraseAll();
    map.makeEdge();

    Point p1(5, 5), p2;
    map[p1] = SNAKE_HEAD;
    GameManager game(map, p1);

    init_pair(POISON_ITEM, COLOR_RED, COLOR_RED);
    init_pair(WALL, COLOR_BLUE, COLOR_BLUE);
    init_pair(IMMUNE_WALL, COLOR_BLUE, COLOR_BLUE);
    init_pair(EMPTY_SPACE, COLOR_WHITE, COLOR_WHITE);
    init_pair(GROWTH_ITEM, COLOR_GREEN, COLOR_GREEN);
    init_pair(SNAKE_BODY, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(SNAKE_HEAD, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(GATE, COLOR_MAGENTA, COLOR_MAGENTA);

    // Snake snake(map);
    // snake.makeSnake();
    
    map.draw();
    
    EventControl event;

    time_t past;
    time_t now;
    
    int key, length = 3;
    int direction = rand() % 4;
    switch(direction) {
        case UP: direction = KEY_UP; break;
        case DOWN: direction = KEY_DOWN; break;
        case RIGHT: direction = KEY_RIGHT; break;
        case LEFT: direction = KEY_LEFT; break;
    }
    bool gateGenerated = false;
    time(&past);

    while (event.isGameOver()) {
        keypad(stdscr, true);
        for (int i=0; i<10; i++) {
            key = getch();
            napms(10);
            if (!(key == KEY_DOWN || key == KEY_UP ||
                key == KEY_LEFT || key == KEY_RIGHT))
                key = direction;
            else
                direction = key;
        }
        keypad(stdscr, false);

        // snake.findRoute(key);
        p2 = p1;
        
        switch (key) {
            case KEY_DOWN: p1.row += 1; break;
            case KEY_UP: p1.row -= 1; break;
            case KEY_LEFT: p1.col -= 1; break;
            case KEY_RIGHT: p1.col += 1; break;
        }

        if (map[p1] == GROWTH_ITEM)
            event.hitsGrowthItem = true;
        else if (map[p1] == POISON_ITEM)
            event.hitsPoisonItem = true;
        else if (map[p1] == WALL)
            event.hitsWall = true;
    
        if (event.hitsGrowthItem) {
            // snake.length++;
            event.hitsGrowthItem = false;
            game.growthItemRecord++;
            for (int i=0; i<game.growthItems.size(); i++)
                if (game.growthItems[i] == p1) {
                    game.growthItems.erase(game.growthItems.begin() + i);
                    break;
                }
            length++;
        }
        else if (event.hitsPoisonItem) {
            // snake.length--;
            event.hitsPoisonItem = false;
            game.poisonItemRecord++;
            for (int i=0; i<game.poisonItems.size(); i++)
                if (game.poisonItems[i] == p1) {
                    game.poisonItems.erase(game.poisonItems.begin() + i);
                    break;
                }
            length--;
        }
        
        if (event.hitsGate) {
            // snake.passGate(game.gates);
            event.hitsGate = false;
            game.gateUsageRecord++;
        }
        else {
            // snake.move(direction);
            map[p2] = EMPTY_SPACE;
            map[p1] = SNAKE_HEAD;
        }
    
        // game.gameStatusChange();
        game.randomItemGenerate();
        if (length > 10 && !gateGenerated) {
            game.randomGateGenerate();
            gateGenerated = true;
        }
    
        map.draw();
        mvwprintw(scoreWindow, 1, 1, "Score Board");
        mvwprintw(scoreWindow, 2, 1, "B: %d/%d (current length) / (max length)", length, game.maxLengthRecord);
        mvwprintw(scoreWindow, 3, 1, "+: %d (Growth Items count)", game.growthItemRecord);
        mvwprintw(scoreWindow, 4, 1, "-: %d (Poison Items count)", game.poisonItemRecord);
        mvwprintw(scoreWindow, 5, 1, "G: %d (Gate usage)", game.gateUsageRecord);
        mvwprintw(scoreWindow, 6, 1, "time: %.2lf(s)", game.seconds);

        mvwprintw(missionWindow, 1, 1, "Mission");
        mvwprintw(missionWindow, 2, 1, "B: 10 (%c)", (game.maxLengthRecord >= 10) ? 'v' : ' ');
        mvwprintw(missionWindow, 3, 1, "+: 5 (%c)", (game.growthItemRecord >= 5) ? 'v' : ' ');
        mvwprintw(missionWindow, 4, 1, "-: 2 (%c)", (game.poisonItemRecord >= 2) ? 'v' : ' ');
        mvwprintw(missionWindow, 5, 1, "G: 1 (%c)", (game.gateUsageRecord >= 1) ? 'v' : ' ');
        
        game.maxLengthRecord = (game.maxLengthRecord < length) ? length : game.maxLengthRecord;

        wrefresh(mainWindow);
        wrefresh(missionWindow);
        wrefresh(scoreWindow);
        time(&now);
        game.seconds = difftime(now, past);
        game.frame++;
    }
    endwin();
    return 0;
}