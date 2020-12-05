#ifndef MAZE_H
#define MAZE_H

#include "MCell.h"
#include <iostream>
#include <algorithm>

class Maze {
	MCell* m_field;
public:
	int dimN, dimM;
	
	Maze(int n, int m);
	const MCell& cell(int i, int j) const;
	bool hasConnection(int i1, int j1, int i2, int j2);
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	bool inBorders(int i1, int j1);
	void printMaze();
	char printDir(int i, int j);
	MCell* getCell(int i, int j);
	~Maze();
};

#endif