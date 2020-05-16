#include <ncurses.h>

using namespace std;

class Point
{
public:
	int x;
	int y;
}

class Snake
{
public:
	void move(int dir);

	int length;
	Point points[100];
};

void eraseScreen();
void makeEdge();
void makeSnake();

int main()
{
	int row, col;

	intitscr();
	getmaxyx(stdscr, row, col);
	keypad(stdscr, TRUE);

	int screen[row][col];
	eraseScreen();
	makeEdge();
	Snake s;

	char key;
	while (gameOver()) {
		key = keyInput();
		direction = findMovement(key);
		Snake.move(direction);
		refresh();
	}

	return 0;
}
