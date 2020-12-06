#include <iostream>
#include "Maze.h"
using namespace std;

int main()
{
    const int dN = 5;
    const int dM = 5;

    Maze maze(dN, dM);

    // Лабиринт по диагонали
    int j = 0;
    for (int i = 0; i < dN * dM; i++) {
        if (i == j) {
            maze.makeConnection(i, j, i, j + 1);
            maze.makeConnection(i, j + 1, i + 1, j + 1);
        }
        j++;
    }

    //Печатаем лабиринт
    maze.printMaze();
}