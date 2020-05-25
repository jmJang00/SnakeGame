#include <ncurses.h>
#include <vector>

// screen block code
#define EMPTY_SPACE 0
#define WALL 1
#define IMMUNE_WALL 2
#define SNAKE_HEAD 3
#define SNAKE_BODY 4
#define GROWTH_ITEM 5
#define POISON_ITEM 6

class Point
{
public:
    Point(int row, int col): row(row), col(col);
    int row;
    int col;
};

class Snake
{
public:
    Snake();
    Snake(SnakeMap &m);
    ~Snake();

    void makeSnake();
    void move(int dir);
    int findRoute(int key);
    void passGate();

    int length;
    int prevKey;
    Point head;
    vector<Point> body;
};

class EventControl
{
public:
    static bool hitsWall;
    static bool hitsPoisonItem;
    static bool hitsGrowthItem;
    static bool hitsGate;
    static bool gameOver;

    static bool decideStatus(SnakeMap &map);
    static bool isGameOver(SnakeMap &map);
};

class SnakeMap
{
public:
    SnakeMap();
    SnakeMap(WINDOW *w, int row, int col);
    ~SnakeMap();

    void eraseAll();
    void makeEdge();

    int **map;
    int row;
    int col;
};

class GameManager
{
public:
    GameManager(SnakeMap &m);
    void randomItemGenerate();
    void randomGateGenerate();
    void itemStatusChange();
    void gateStatusChange();

    SnakeMap& map;
    vector<Point> poisonItems;
    vector<Point> growthItems;
    Point gates[2];
};

using namespace EventControl;
using namespace std;

// KEY_LEFT KEY_RIGHT KEY_UP KEY_DOWN

int main()
{
    int row, col;

    initscr();
    getmaxyx(stdscr, row, col);
    keypad(stdscr, TRUE);
    noecho();

    SnakeMap map;
    map.eraseAll();
    map.makeEdge();

    Snake snake(map);
    snake.makeSnake()

    GameManager game(m);

    int ch, direction;
    while (isGameOver()) {
	key = getch();
	direction = snake.findRoute(key);

	if (hitsGrowthItem)
	    length++;
	else if (hitsPoisonItem)
	    length--;

	if (hitsGate)
	    snake.passGate();
	else
	    snake.move(direction);

	game.itemStatusChange();
	game.randomItemGenerate();
	game.gateStatusChange();
	game.randomGateGenerate();

	if (s.length == 10)
	    map.makeGate();

	refresh();
    }

    return 0;
}
