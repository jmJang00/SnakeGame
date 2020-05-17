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
	int x;
	int y;
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

	int **map;
	int length;
	Point head;
	vector<Point> body;
};

class SnakeMap
{
public:
	SnakeMap();
	SnakeMap(WINDOW *w, int row, int col);
	~SnakeMap();
	void eraseAll();
	void makeEdge();
	void makeGate();
	void reflectResult();

	int **map;
	int row;
	int col;
};

class EventControl
{
public:
   static bool hitsWall(SnakeMap &map);
   static int hitsItem(SnakeMap &map, int dir);
   static bool hitsGate(SnakeMap &map, int dir);
   static bool decideStatus(SnakeMap &map);
   static bool isGameOver(SnakeMap &map);

   bool gameOver;
};

class ItemManager
{
public:
	class Item {
		int kind;
		int leftTurns;
	};

	ItemManager(SnakeMap &s);
	void randomItemGenerate();
	void itemStatusChange();

	int **map;
	vector<Item> list;
};

using namespace EventControl;
using namespace std;

int main()
{
	int row, col;

	initscr();
	getmaxyx(stdscr, row, col);
	keypad(stdscr, TRUE);
	noecho();

	SnakeMap m;
	m.eraseAll();
	m.makeEdge();

	Snake s(m);
	s.makeSnake()

	ItemManager im(m);

	int ch, direction;
	while (isGameOver()) {
		ch = getch();
		direction = s.findRoute(ch);

		switch (hitsItem(m, direction)) {
			case GROWTH_ITEM:
			    s.length++;
				break;
			case POISON_ITEM:
			    s.length--;
				break;
		}

		if (hitsGate(m, direction))
			s.passGate();
		else
			s.move(direction);

		im.itemStatusChange();
		im.randomItemGenerate();

		if (s.length == 10)
			m.makeGate();

		m.reflectResult();

		refresh();
	}

	return 0;
}
