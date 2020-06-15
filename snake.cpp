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
	int x = rand() % maxheight;
	int y = rnnd() % maxwidth;
	head(x,y);
	for (int i = 0; i < length; i++)
	{
		body.push_back();
	}
	for (int i = 0; i < length; i++)
	{
		body.begin() + i = head.col + (i + 1);
	}

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
		point p (head.row,head.col);
		head.col++;
		body.insert(body.begin, p);
	}
}
int Snake::findRoute(int key) {
	int s = key;
	while (1)
	{
		


	}
}
void Snake::passGate(Point *gates) {}