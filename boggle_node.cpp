#include "boggle_node.h"

#include <iostream>

BoggleNode::BoggleNode(char c, int index) : currentIndex(index)
{
	prefix = std::string(1, c);
	trail.insert(index);
}

BoggleNode::BoggleNode(const BoggleNode &node)
{
	prefix = std::string(node.prefix);
	trail = std::set<int>(node.trail);
	currentIndex = node.currentIndex;
}

void BoggleNode::appendChar(char c)
{
	prefix += c;
}

void BoggleNode::appendIndex(int index)
{
	currentIndex = index;
	trail.insert(index);
}

bool BoggleNode::hasVisited(int index)
{
	return trail.find(index) != trail.end();
}
