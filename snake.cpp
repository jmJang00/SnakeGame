#include "snake.h"
#include <cstdlib>

Snake::Snake() {}
Snake::Snake(SnakeMap& m) {}
~Snake() {}

void Snake::makeSnake()
{
	head(rand() % maxheight, rnnd() % maxwidth);
}
void Snake::move(int dir)
{
	int dir = getch();
	switch (dir)
	{
		case KEY_LEFT:
			if (direction != 2)
				direction = 3;
			break;
		case KEY_UP;
			if (direction != 1)
				direction = 0;
			break;
		case KEY_DOWN;
			if (direction != 0)
				direction = 1;
			break;
		case KEY_RIGHT;
			if (direction != 3)
				direction = 2;
			break;
	}
	if (direction == 3)
	{
		head.insert()
	}
}
int Snake::findRoute(int key) {}
int Snake::passGate() {}
