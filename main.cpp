#include <ncurses.h>
#include <iostream>
#include "snake.h"
#include "SnakeMap.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include "constant.h"
// screen block code


using namespace std;
using std::vector;

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
    bool decideStatus(SnakeMap &map);
    bool isGameOver(SnakeMap &map) {
        if (hitsWall)
           return false;
        else
           return true;
    }
};

class GameManager
{
public:
    GameManager(SnakeMap &m, Point& p):
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
        PoisonItemRecord = 0;
        gateUsageRecord = 0;
    }
    void randomItemGenerate() {
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
    void randomGateGenerate() {
        for (int i=0; i<2; i++) {
            int idx = rand() % wall.size();
            gates[0] = wall[idx];
            map[gates[0]] = GATE;
            wall.erase(wall.begin() + idx);
        }
    }
    void gameStatusChange() {}
    void gameScoreChange() {}

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
    unsigned int PoisonItemRecord;
    unsigned int gateUsageRecord;
    
    
    Point gates[2];
};

// class Mission {};

int main()
{
    int row, col;

    // configure
    initscr();
    getmaxyx(stdscr, row, col);
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    srand(time(NULL));

    int mainWinR = row;
    int mainWinC = col / 2;
    Point mainWinLoc(0, 0);

    int scoreWinR = row / 2;
    int scoreWinC = col - mainWinC;
    Point scoreWinLoc(0, mainWinC-1);

    int missionWinR = row - scoreWinR;
    int missionWinC = scoreWinC;
    Point missionWinLoc(scoreWinR-1, mainWinC-1);

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
    
    int direction;
    direction = getch();
    nodelay(stdscr, TRUE);
    
    int key, length = 3;
    bool gateGenerated = false;
    time(&now);
    while (event.isGameOver(map)) {
        key = getch();
        if (!(key == KEY_DOWN || key == KEY_UP || key == 's' ||
            key == KEY_LEFT || key == KEY_RIGHT || key == 'q'))
            key = direction;

        // direction = snake.findRoute(key);    
        p2 = p1;
        direction = key;
        switch (key) {
            case KEY_DOWN:
                p1.row += 1;
                break;
            case KEY_UP:
                p1.row -= 1;
                break;
            case KEY_LEFT:
                p1.col -= 1;
                break;
            case KEY_RIGHT:
                p1.col += 1;
                break;
            case 's':
                continue;
            case 'q':
                event.gameOver = true;
                break;
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
        
        wrefresh(mainWindow);
        wrefresh(missionWindow);
        wrefresh(scoreWindow);
        napms(100);
        past = now;
        time(&now);
        game.seconds = difftime(now, past);
        game.frame++;
    }
    
    endwin();
    return 0;
}