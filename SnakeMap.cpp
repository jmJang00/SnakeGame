#include "SnakeMap.h"
#include <ncurses.h>

using namespace std;

SnakeMap::SnakeMap(int row, int col): row(row), col(col) {
    mat = new int*[row];
    for (int i=0; i<row; i++) {
       mat[i] = new int[col];
    }
}

SnakeMap::~SnakeMap() {
    for (int i=0; i<row; i++)
	    delete[] mat[i];
    delete[] mat;
}

void SnakeMap::eraseAll() {
    for (int i=0; i<row; i++)
	    for (int j=0; j<col; j++)
	        mat[i][j] = 0;
}

void SnakeMap::makeEdge() {
    mat[0][0] = 2;
    mat[0][col-1] = 2;
    mat[row-1][0] = 2;
    mat[row-1][col-1] = 2;
    for (int i=0; i<row; i++) {
	    for (int j=0; j<col; j++) {
	        if ((i == 0 || i == row-1) ^ (j == 0 || j == col-1))
		        mat[i][j] = 1;
	    }
    }
}

void SnakeMap::draw() {
    for (int i=0; i<row; i++) {
	    for (int j=0; j<col; j++) {
	        attron(COLOR_PAIR(mat[i][j]));
	        mvprintw(i, j, " ");
	        attroff(COLOR_PAIR(mat[i][j]));
	    }
    }
}