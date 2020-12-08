#include <iostream>
#include "MTreeNode.h"

const int childMax = 4;

MTreeNode::MTreeNode(MTreeNode* parent, int i, int j, int distance) {
	m_parent = parent;
	m_children = new MTreeNode * [childMax];
	m_i = i;
	m_j = j;
	m_distance = distance;
	m_childCount = 0;
}

bool MTreeNode::addChild(int i, int j) {
	if (m_childCount >= childMax || hasChild(i, j) != nullptr)
		return false;
	auto child = new MTreeNode(this, i, j, m_distance + 1);
	m_children[m_childCount] = child;
	m_childCount++;
	return true;
}


MTreeNode* MTreeNode::hasChild(int i, int j) {
	for (int n = 0; n < m_childCount; n++) {
		auto thisChild = *(m_children + n);
		if (thisChild != nullptr && thisChild->m_i == i && thisChild->m_j == j)
			return thisChild;
		auto childOfChildren = thisChild->hasChild(i, j);
		if (childOfChildren != nullptr)
			return childOfChildren;
	}
	return nullptr;
}

MTreeNode* MTreeNode::beginTree(int i, int j) {
	MTreeNode* treeNode = new MTreeNode(nullptr, i, j, 0);
	return treeNode;
}

const MTreeNode* MTreeNode::child(int i) const {
	if (i < 0 || i >= m_childCount)
		return nullptr;
	else {
		auto thisChild = *(m_children + i);
		if (thisChild != nullptr)
			return thisChild;
		else
			return nullptr;
	}
}

MTreeNode::~MTreeNode() {
	delete[] m_children;
}