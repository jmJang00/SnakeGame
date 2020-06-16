#include "Snake.h"

Snake::Snake(SnakeMap& m, EventControl& e): map(m), event(e) {
	bodyLength = 2;
	prevKey = 0;
}

int Snake::makeSnake()
{
	head.row = (map.row - 2) / 2;
    head.col = (map.col - 2) / 2;
	map[head] = SNAKE_HEAD;

    int initDir = rand() % 4;
	
	switch(initDir) {
		case UP: prevKey = KEY_DOWN; break;
		case DOWN: prevKey = KEY_UP; break;
		case RIGHT: prevKey = KEY_LEFT; break;
		case LEFT: prevKey = KEY_RIGHT; break;
	}

    Point bodytemp(head);
	for (int i = 0; i < bodyLength; i++)
	{
		switch(initDir) {
			case UP: bodytemp.row--; break;
			case DOWN: bodytemp.row++; break;
			case RIGHT: bodytemp.col++; break;
			case LEFT: bodytemp.col--; break;
	    }
		body.push_front(Point(bodytemp.row, bodytemp.col));
	}
	return prevKey;
}
void Snake::move(Point next)
{
	map[head] = SNAKE_BODY;
	body.push_front(head);

	for (int i=0; i < body.size() - bodyLength; i++) {
		map[body.back()] = EMPTY_SPACE;
		body.pop_back();
	}

    map[next] = SNAKE_HEAD;
	head = next;
}
Point Snake::findRoute(int key) {
	if (!event.hitsGate && (key == KEY_DOWN && prevKey == KEY_UP) ||
	    (key == KEY_UP && prevKey == KEY_DOWN) ||
		(key == KEY_LEFT && prevKey == KEY_RIGHT) ||
		(key == KEY_RIGHT && prevKey == KEY_LEFT)) {
			event.gameOver = true;
			return head;
	}

	Point p(head);

	switch (key) {
		case KEY_DOWN: p.row += 1; break;
		case KEY_UP: p.row -= 1; break;
		case KEY_LEFT: p.col -= 1; break;
		case KEY_RIGHT: p.col += 1; break;
	}

	switch (map[p]) {
		case GROWTH_ITEM: event.hitsGrowthItem = true; break;
		case POISON_ITEM: event.hitsPoisonItem = true; break;
		case GATE: event.hitsGate = true; break;
		case IMMUNE_WALL: case WALL: event.gameOver = true; break;
		case SNAKE_BODY: event.gameOver = true; break;
	}

	return p;
}
int Snake::passGate(const Point *gates, Point next, int key) {
	Point exitGate; 
	if (gates[0] == next)
	    exitGate = gates[1];
	else if (gates[1] == next)
	    exitGate = gates[0];
	
	switch(key) {
		case KEY_UP: key = UP; break;
		case KEY_DOWN: key = DOWN; break;
		case KEY_RIGHT: key = RIGHT; break;
		case KEY_LEFT: key = LEFT; break;
	}

    int direction = 0;
	for (int i=0; i<4; i++) {
		Point temp(exitGate);
		switch(key) {
            case UP: temp.row--; direction = KEY_UP; break;
            case DOWN: temp.row++; direction = KEY_DOWN; break;
            case RIGHT: temp.col++; direction = KEY_RIGHT; break;
            case LEFT: temp.col--; direction = KEY_LEFT; break;
        }
		if (temp.row >= 0 && temp.row < map.row &&
		    temp.col >= 0 && temp.col < map.col && map[temp] == EMPTY_SPACE) {
			exitGate = temp;
			break;
		}
		key = (key + 1) % 4;
	}
	move(exitGate);
	prevKey = direction;
	return direction;
}

bool Snake::isSnake(Point p) {
	if (p == head)
	    return true;
	
	for (int i=0; i<body.size(); i++)
        if (body[i] == p)
		    return true;

    return false;
}