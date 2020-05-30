#ifndef __SNAKE_MAP__
#define __SNAKE_MAP__

class SnakeMap
{
public:
    SnakeMap();
    SnakeMap(int row, int col);
    ~SnakeMap();

    void eraseAll();
    void makeEdge();

    int **map;
    int row;
    int col;
};

#endif
