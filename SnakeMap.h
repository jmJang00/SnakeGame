#ifndef __SNAKE_MAP__
#define __SNAKE_MAP__
#include <ncurses.h>

class Point
{
public:
    Point(): row(0), col(0) {}
    Point(int row, int col): row(row), col(col) {}
    Point(const Point& p) {
        row = p.row;
        col = p.col;
    }
    virtual ~Point() {}
    Point &operator =(const Point p) {
        row = p.row;
        col = p.col;
        return *this;
    }
    bool operator ==(const Point p) const {
        return row == p.row && col == p.col;
    }

    bool operator !=(const Point p) {
        return !(*this == p);
    }
    int row;
    int col;
};

class Item: public Point
{
public:
    int lifespan;

    Item(int i, Point p): lifespan(i), Point::Point(p) {}
    Item(const Item& item): Point::Point(item.row, item.col) {
        lifespan = item.lifespan;
    }
    Item(): lifespan(0) {}

    Item &operator =(const Point p) {
        Point::operator=(p);
        return *this;
    }
    bool operator ==(const Point p) {
        return Point::operator==(p);
    }
    bool operator !=(const Point p) {
        return !(*this == p);
    }
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
