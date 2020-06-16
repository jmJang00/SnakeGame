#include <ncurses.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Snake.h"
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
    curs_set(0);

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

    while (true) {
        map.eraseAll();
        map.makeEdge();
        EventControl event;

        Snake snake(map, event);
        int inertia = snake.makeSnake();

        GameManager game(map, snake);

        init_pair(POISON_ITEM, COLOR_RED, COLOR_RED);
        init_pair(WALL, COLOR_BLUE, COLOR_BLUE);
        init_pair(IMMUNE_WALL, COLOR_BLUE, COLOR_BLUE);
        init_pair(EMPTY_SPACE, COLOR_WHITE, COLOR_WHITE);
        init_pair(GROWTH_ITEM, COLOR_GREEN, COLOR_GREEN);
        init_pair(SNAKE_BODY, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(SNAKE_HEAD, COLOR_RED, COLOR_RED);
        init_pair(GATE, COLOR_MAGENTA, COLOR_MAGENTA);
        
        map.draw();

        time_t past;
        time_t now;
        
        int key;
        bool gateGenerated = false;
        time(&past);

        while (event.isGameOver()) {
            keypad(stdscr, true);
            for (int i=0; i<10; i++) {
                key = getch();
                napms(10);
                if (!(key == KEY_DOWN || key == KEY_UP ||
                    key == KEY_LEFT || key == KEY_RIGHT))
                    key = inertia;
                else
                    inertia = key;
            }
            keypad(stdscr, false);

            Point next = snake.findRoute(key);

            
            if (event.hitsGrowthItem) {
                snake.bodyLength++;
                event.hitsGrowthItem = false;
                game.growthItemRecord++;
                for (auto it=game.growthItems.begin(); it != game.growthItems.end(); it++)
                    if (*it == next) {
                        game.emptySpace.push_back(*it);
                        game.growthItems.erase(it);
                        break;
                    }
            }
            else if (event.hitsPoisonItem) {
                snake.bodyLength--;
                event.hitsPoisonItem = false;
                game.poisonItemRecord++;
                for (auto it=game.poisonItems.begin(); it != game.poisonItems.end(); it++)
                    if (*it == next) {
                        game.emptySpace.push_back(*it);
                        game.poisonItems.erase(it);
                        break;
                    }
            }
            
            if (event.gameOver || snake.bodyLength < 2) {
                break;
            }

            if (event.hitsGate) {
                inertia = snake.passGate(game.gates, next, key);
                event.hitsGate = false;
                game.gateUsageRecord++;
            }
            else {
                snake.move(next);
                snake.prevKey = key;
            }
        
            game.itemStatusChange();
            game.randomItemGenerate();
            if (snake.bodyLength + 1 > 4 && !gateGenerated) {
                game.randomGateGenerate();
                gateGenerated = true;
            }
        
            map.draw();
            mvwprintw(scoreWindow, 1, 1, "Score Board");
            mvwprintw(scoreWindow, 2, 1, "B: %d/%d (current length) / (max length)", snake.bodyLength + 1, game.maxLengthRecord);
            mvwprintw(scoreWindow, 3, 1, "+: %d (Growth Items count)", game.growthItemRecord);
            mvwprintw(scoreWindow, 4, 1, "-: %d (Poison Items count)", game.poisonItemRecord);
            mvwprintw(scoreWindow, 5, 1, "G: %d (Gate usage)", game.gateUsageRecord);
            mvwprintw(scoreWindow, 6, 1, "time: %.2lf(s)", game.seconds);

            mvwprintw(missionWindow, 1, 1, "Mission");
            mvwprintw(missionWindow, 2, 1, "B: 10 (%c)", (game.maxLengthRecord >= 10) ? 'v' : ' ');
            mvwprintw(missionWindow, 3, 1, "+: 5 (%c)", (game.growthItemRecord >= 5) ? 'v' : ' ');
            mvwprintw(missionWindow, 4, 1, "-: 2 (%c)", (game.poisonItemRecord >= 2) ? 'v' : ' ');
            mvwprintw(missionWindow, 5, 1, "G: 1 (%c)", (game.gateUsageRecord >= 1) ? 'v' : ' ');
            
            game.maxLengthRecord = (game.maxLengthRecord < snake.bodyLength + 1) ? snake.bodyLength + 1 : game.maxLengthRecord;

            wrefresh(mainWindow);
            wrefresh(missionWindow);
            wrefresh(scoreWindow);
            time(&now);
            game.seconds = difftime(now, past);
            game.frame++;
        }

        map.gameEnding();
        
        nodelay(stdscr, FALSE);
        int ch = 0;
        while ((ch = getch()) != 'r' && ch != 'q') {}
        if (ch == 'q')
            break;
        nodelay(stdscr, TRUE);
    }
    endwin();
    return 0;
}