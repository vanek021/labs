#include <iostream>
#include "Maze.h"
#include "MTreeNode.h"

using namespace std;

void prepareTree(MTreeNode* node, Maze& maze) {
    int i = node->i(); int j = node->j();

    if (i + 1 < maze.dimN && maze.hasConnection(i, j, i + 1, j)) {
        if (node->addChild(i + 1, j)) {
            auto thisChild = node->hasChild(i + 1, j);
            prepareTree(thisChild, maze);
        }
    }

    if (j + 1 < maze.dimM && maze.hasConnection(i, j, i, j + 1)) {
        if (node->addChild(i, j + 1)) {
            auto thisChild = node->hasChild(i, j + 1);
            prepareTree(thisChild, maze);
        }
    }
}

void printTree(MTreeNode* node, Maze& maze) {
    cout << node->distance() << " ";
    for (int i = 0; i < maze.dimN; i++) {
        for (int j = 0; j < maze.dimM; j++) {
            if (i == 0 && j == 0)
                continue;
            auto thisChild = node->hasChild(i, j);
            if (thisChild == nullptr)
                cout << 'X' << ' ';
            else
                cout << thisChild->distance() << " ";
        }
        cout << endl;
    }
}

int main()
{
    /* TASK 8
    const int dN = 5;
    const int dM = 5;
    Maze maze(dN, dM);
    int j = 0;
    for (int i = 0; i < dN * dM; i++) {
        if (i == j) {
            maze.makeConnection(i, j, i, j + 1);
            maze.makeConnection(i, j + 1, i + 1, j + 1);
        }
        j++;
    }
    maze.printMaze(); */
    
    // TASK 9
    const int dN = 5;
    const int dM = 5;

    Maze maze2(dN, dM);

    for (int i = 0; i < dN; i++)
        for (int j = 0; j < dM; j++) {
            if (j >= i && j + 1 < dM)
                maze2.makeConnection(i, j, i, j + 1);
            if (j <= i + 1 && i + 1 < dN)
                maze2.makeConnection(i, j, i + 1, j);
        }
    cout << "Maze" << endl;
    maze2.printMaze();
    cout << endl << "Tree" << endl;
    
    MTreeNode* node = MTreeNode::beginTree(0, 0);
    prepareTree(node, maze2);
    printTree(node, maze2);

}