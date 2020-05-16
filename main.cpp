#include <ncurses.h>

using namespace std;

class Snake
{
public:
	void move(int dir);
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
	Snake s = new Snake();

	char key;
	while (gameOver()) {
		key = keyInput();
		direction = findMovement(key);
		Snake.move(direction);
		refresh();
	}

	return 0;
}
