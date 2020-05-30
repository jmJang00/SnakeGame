#include "SnakeMap.h"

SnakeMap::SnakeMap() {}

SnakeMap::SnakeMap(int row, int col) {
    map = new int*[row];
    for (int i=0; i<row; i++) {
       map[i] = new int[col];
    }
}

SnakeMap::~SnakeMap() {
    for (int i=0; i<row; i++)
	    delete[] map[i];
    delete[] map;
}

void SnakeMap::eraseAll() {
    for (int i=0; i<row; i++)
	    for (int j=0; j<col; j++)
	        map[i][j] = 0;
}

void SnakeMap::makeEdge() {
    map[0][0] = 2;
    map[0][col-1] = 2;
    map[row-1][0] = 2;
    map[row-1][col-1] = 2;
    for (int i=0; i<row; i++) {
	    for (int j=0; j<col; j++) {
	        if ((i == 0 || i == row-1) ^ (j == 0 || j == col-1))
		        map[i][j] = 1;
	    }
    }
}
