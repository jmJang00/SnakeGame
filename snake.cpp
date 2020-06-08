#include "snake.h"
#include <cstdlib>
#include "SnakeMap.h"

Snake::Snake(SnakeMap& m) {
	length = 2;
	head.row = m.row;
	head.col = m.col;
}
Snake::~Snake() {}

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
		head.insert();
		head=Snake::body.begin()
		Snake::body.pop_back();
	}
}
int Snake::findRoute(int key) {
	int s = key;
	while (1)
	{
		if (s == 0)
			break;
		else if (s == 1)
			EventControl::isGameover();
		else if (s==4)
			EventControl::isGameover();
		


	}
}
void Snake::passGate(Point *gates) {}