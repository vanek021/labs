#ifndef MTREENODE_H
#define MTREENODE_H

#include <iostream>
#include <algorithm>

class MTreeNode;

class MTreeNode {
	int m_i;
	int m_j;
	MTreeNode* m_parent;
	MTreeNode** m_children;
	int m_distance;
	int m_childCount;

	MTreeNode(MTreeNode* parent, int i, int j, int distance);
	~MTreeNode();

public:
	int i() const { return m_i; }
	int j() const { return m_j; }
	int distance() const { return m_distance; }
	const MTreeNode* parent() const { return m_parent; }
	const MTreeNode* child(int i) const;
	int childCount() const { return m_childCount; }
	bool addChild(int i, int j);
	MTreeNode* hasChild(int i, int j);
	static MTreeNode* beginTree(int i, int j);
	static MTreeNode* searchNode(const MTreeNode& tree, const int i, const int j);
};
#endif