#ifndef __SNAKE_H__
#define __SNAKE_H__

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

#endif __SNAKE_H__
