#include <ncurses.h>
#include <iostream>
// #include "snake.h"
#include "SnakeMap.h"
#include <vector>
#include <ctime>
#include <cstdlib>

// screen block code
#define EMPTY_SPACE 0
#define WALL 1
#define IMMUNE_WALL 2
#define SNAKE_HEAD 3
#define SNAKE_BODY 4
#define GROWTH_ITEM 5
#define POISON_ITEM 6
#define GATE 7

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3


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

    EventControl() {
        cout << this << ": EventControl() called";
        hitsWall = false;
        hitsPoisonItem = false;
        hitsGrowthItem = false;
        hitsGate = false;
        gameOver = false;
    }
    ~EventControl() {
        cout << this << ": ~EventControl() called";
    }
    bool decideStatus(SnakeMap &map);
    bool isGameOver(SnakeMap &map) {
        if (EventControl::hitsWall)
           return false;
        else
           return true;
    }
};

class GameManager
{
public:
    GameManager(SnakeMap &m, Point& p): map(m), snake(p), turn(0) {    // Point& p temporary
        cout << this << ": GameManager() called";
        for (int i=0; i<map.row; i++) {
            for (int j=0; j<map.col; j++) {
                if (map.mat[i][j] == EMPTY_SPACE)
                    emptySpace.push_back(Point(i, j));
                else if (map.mat[i][j] == WALL)
                    wall.push_back(Point(i, j));
            }
        }
    }
    ~GameManager() {
        cout << this << ": ~GameManager() called";
    }
    void randomItemGenerate() {
        if (turn % 10 != 0)
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
    void gameStatusChange() {
        
    }

    Point snake;    // temporary
    SnakeMap map;
    vector<Point> poisonItems;
    vector<Point> growthItems;
    vector<Point> wall;
    // vector<Point> snake;
    vector<Point> emptySpace;
    unsigned int turn;
    
    Point gates[2];
};


// KEY_LEFT KEY_RIGHT KEY_UP KEY_DOWN

int main()
{
    int row, col;

    initscr();
    getmaxyx(stdscr, row, col);
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    srand(time(NULL));

    SnakeMap map(row, col);

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
    
    int direction, key, length = 3;
    bool gateGenerated = false;
    while (event.isGameOver(map)) {
        key = getch();

        // direction = snake.findRoute(key);    
        p2 = p1;
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
    
        // game.itemStatusChange();
        game.randomItemGenerate();
        // game.gateStatusChange();
        if (length > 5 && !gateGenerated) {
            game.randomGateGenerate();
            gateGenerated = true;
        }
    
        map.draw();
        refresh();
        game.turn++;
    }
    
    endwin();
    return 0;
}