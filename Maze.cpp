#include <iostream>
#include "Maze.h"
#include "MCell.h"

using namespace std;

Maze::Maze(int n, int m) {
	dimM = m; dimN = n;
	m_field = new MCell[n * m];
}

const MCell& Maze::cell(int i, int j) const {
	return m_field[i * dimN + j];
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2) {
	if (j1 == j2 && abs(i2 - i1) == 1 ) {
		if (i2 > i1 && m_field[i1 * dimN + j1].down() 
			|| i1 > i2 && m_field[i2 * dimN + j2].down())
			return true;
	}
	else if (i1 == i2 && abs(j2-j1) == 1) {
		if (j2 > j1 && m_field[i1 * dimN + j1].right()
			|| j1 > j2 && m_field[i2 * dimN + j2].right()) {

			return true;
		}
	}
	return false;
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2) {
	if (!inBorders(i1, j1) || !inBorders(i2, j2))
		return false;
	if (j1 == j2 && abs(i2 - i1) == 1) {
		if (i2 - i1 == 1)
			m_field[i1 * dimN + j1].m_down = true;
		else
			m_field[i2 * dimN + j2].m_down = true;
		return true;
	}
	else if (i1 == i2 && abs(j2 - j1) == 1) {
		if (j2 - j1 == 1)
			m_field[i1 * dimN + j1].m_right = true;
		else
			m_field[i2 * dimN + j2].m_right = true;
		return true;
	}
	return false;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2) {
	if (!inBorders(i1, j1) || !inBorders(i2, j2))
		return false;
	if (!hasConnection(i1, j1, i2, j2))
		return false;
	else {
		m_field[i1 * dimN + j1].m_down = false;
		m_field[i1 * dimN + j1].m_right = false;
		return true;
	}
}

bool Maze::inBorders(int i1, int j1) {
	return j1 >= 0 && j1 < dimN && i1 >= 0 && i1 < dimM;
}

void Maze::printMaze() {
	for (int i = 0; i < dimN; i++) {
		for (int j = 0; j < dimM; j++) {
			cout << printDir(i, j);
		}
		cout << endl;
	}
}

Maze::~Maze() {
	delete[] m_field;
}

MCell* Maze::getCell(int i, int j) {
	if (i < 0 || j < 0 || j >= dimM || i >= dimN)
		return nullptr;
	else return &m_field[i * dimN + j];
}

char Maze::printDir(int i, int j) {
	auto top = getCell(i - 1, j);
	auto left = getCell(i, j - 1);
	if (top == nullptr && left == nullptr) {
		if (m_field[i * dimN + j].down() && m_field[i * dimN + j].right())
			return '0';
	}
	if (top != nullptr && left != nullptr && top->down() && left->right()) {
		if (m_field[i * dimN + j].down() && m_field[i * dimN + j].right())
			return (char)197;
		if (m_field[i * dimN + j].right())
			return (char)193;
		if (m_field[i * dimN + j].down())
			return(char)180;
	}
	if (top != nullptr && top->down()) {
		if (m_field[i * dimN + j].down() && m_field[i * dimN + j].right())
			return (char)195;
		if (m_field[i * dimN + j].right())
			return (char)192;
		if (m_field[i * dimN + j].down())
			return(char)179;
	}
	if (left != nullptr && left->right()) {
		if (m_field[i * dimN + j].down() && m_field[i * dimN + j].right())
			return (char)194;
		if (m_field[i * dimN + j].right())
			return (char)196;
		if (m_field[i * dimN + j].down())
			return(char)191;
	}
	return '0';
}