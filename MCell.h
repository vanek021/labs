#ifndef MCELL_H
#define MCELL_H

#include <iostream>

class MCell {
private:
	MCell() {};

	bool m_down = false;
	bool m_right = false;
public:
	bool right() const { return m_right; };
	bool down() const { return m_down; };

	friend class Maze;
};

#endif