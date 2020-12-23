﻿#include <iostream>
#include "Maze.h"
#include "MTreeNode.h"
#include <queue>

using namespace std;

int maxWeight(const MTreeNode* tree);
void printIntSymbol(MTreeNode* node, int distance);
void printCharSymbol(MTreeNode* node, char symbol);

void printTree(MTreeNode* node, Maze& maze) {
	printIntSymbol(node, node->distance());
	for (int i = 0; i < maze.dimN; i++) {
		for (int j = 0; j < maze.dimM; j++) {
			if (i == 0 && j == 0) continue;
			auto thisChild = node->hasChild(i, j);
			if (thisChild == nullptr)
				printCharSymbol(node, 'X');
			else
				printIntSymbol(node, thisChild->distance());
		}
		cout << endl;
	}
}

void buildFullMaze(Maze& iMaze, const MTreeNode* tree) {
	queue<const MTreeNode*> nodes;
	nodes.push(tree);
	while (true) {
		if (nodes.size() == 0)
			break;
		auto node = nodes.front();
		nodes.pop();
		for (int i = 0; i < node->childCount(); i++) {
			const MTreeNode* child = node->child(i);
			iMaze.makeConnection(node->i(), node->j(), child->i(), child->j());
			nodes.push(child);
		}
	}
}

void TreeWithoutLoops(MTreeNode* tree, int width, int height) {
	queue<MTreeNode*> nodes;
	auto node = tree;
	nodes.push(node);
	while (true) {
		if (nodes.size() == 0)
			break;
		node = nodes.front();
		nodes.pop();
		if (node->i() < 0 || node->i() >= height || node->j() < 0 || node->j() >= width)
			continue;
		for (int dx = -1; dx <= 1; dx++)
			for (int dy = -1; dy <= 1; dy++) {
				if (dx != 0 && dy != 0)
					continue;
				if (!MTreeNode::searchNode(*tree, node->i() + dx, node->j() + dy)) {
					node->addChild(node->i() + dx, node->j() + dy);
					MTreeNode* child = node->hasChild(node->i() + dx, node->j() + dy);
					nodes.push(child);
				}
			}
		
	}
}

int maxWeight(const MTreeNode* tree) {
	queue<const MTreeNode*> nodes;
	nodes.push(tree);
	int maxWeight = 0;
	while (true) {
		if (nodes.size() == 0) break;
		auto node = nodes.front();
		nodes.pop();
		if (node->distance() > maxWeight)
			maxWeight = node->distance();
		for (int i = 0; i < node->childCount(); i++) {
			nodes.push(node->child(i));
		}
	}
	return maxWeight;
}

float averageWeight(const MTreeNode* tree) {
	queue<const MTreeNode*> nodes;
	nodes.push(tree);
	int sumWeight = 0;
	int count = 0;
	while (true) {
		if (nodes.size() == 0) break;
		auto node = nodes.front();
		nodes.pop();
		sumWeight += node->distance();
		count++;
		for (int i = 0; i < node->childCount(); i++) {
			nodes.push(node->child(i));
		}
	}
	return sumWeight / float(count);
}

void printIntSymbol(MTreeNode* node, int distance) {
	if (maxWeight(node) >= 100)
		cout << distance << " ";
	else if (distance >= 10)
		cout << distance << " ";
	else cout << distance << "  ";
}

void printCharSymbol(MTreeNode* node, char symbol) {
	if (maxWeight(node) >= 100)
		cout << symbol << " ";
	else
		cout << symbol << "  ";
}

int main()
{
	// TASK 10
	int dN, dM;
	cout << "Enter dimN and dimM: " << endl;
	cin >> dN >> dM;
	const int i = rand() % dN, j = rand() % dM;
	cout << "Random i: " << i << ", Random j: " << j << endl;
	cout << "Dimension N: " << dN << ", Dimension M: " << dM << endl << endl;
	Maze maze(dN, dM);
	MTreeNode* firstNode = MTreeNode::beginTree(i, j);
	TreeWithoutLoops(firstNode, dN, dM);
	buildFullMaze(maze, firstNode);
	cout << "Printing maze.." << endl;
	maze.printMaze();
	cout << endl << "Printing tree.." << endl;
	printTree(firstNode, maze);
	cout << endl << "Max Weight" << endl;
	cout << maxWeight(firstNode) << endl;
	cout << endl << "Average Weight" << endl;
	cout << averageWeight(firstNode);
}