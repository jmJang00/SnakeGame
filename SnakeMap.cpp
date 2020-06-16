#include "SnakeMap.h"

using namespace std;

SnakeMap::SnakeMap(int row, int col, WINDOW *scr)
: row(row-2), col(col-2), mainWindow(scr)
{
    mat = new int*[row];
    for (int i=0; i<row; i++) {
       mat[i] = new int[col];
    }
    
}

SnakeMap::~SnakeMap() {
    for (int i=0; i<row; i++)
	    delete[] mat[i];
    delete[] mat;
    delwin(mainWindow);
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

void SnakeMap::gameEnding() {
    eraseAll();
    draw();
    mvwprintw(mainWindow, (row-2)/2+0, (col-19)/2, "     Game Over     ");
    mvwprintw(mainWindow, (row-2)/2+1, (col-19)/2, "retry: <r> end: <q>");
    wrefresh(mainWindow);
}

void SnakeMap::draw() {
    for (int i=0; i<row; i++) {
	    for (int j=0; j<col; j++) {
	        wattron(mainWindow, COLOR_PAIR(mat[i][j]));
	        mvwprintw(mainWindow, i+1, j+1, " ");
	        wattroff(mainWindow, COLOR_PAIR(mat[i][j]));
	    }
    }
}