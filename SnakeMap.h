#ifndef __SNAKE_MAP__
#define __SNAKE_MAP__
#include <ncurses.h>

class Point
{
public:
    Point(): row(0), col(0) {}
    Point(int row, int col): row(row), col(col){}
    Point &operator =(Point p) {
        row = p.row;
        col = p.col;
    }
    bool operator ==(Point p) {
        return row == p.row && col == p.col;
    }

    bool operator !=(Point p) {
        return !(*this == p);
    }
    int row;
    int col;
};

class SnakeMap
{
public:
    SnakeMap(int row, int col, WINDOW *scr);
    ~SnakeMap();

    void gameEnding();
    void eraseAll();
    void makeEdge();
    void draw();
    int &operator [](Point p) {
        return mat[p.row][p.col];
    }
    int **mat;
    const int row;
    const int col;
    WINDOW *mainWindow;
};

#endif
