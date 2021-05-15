#ifndef BOGGLE_NODE_H
#define BOGGLE_NODE_H

#include <set>
#include <string>

class BoggleNode
{
	public:
		BoggleNode(char value, int index);
		BoggleNode(const BoggleNode &node);
		void appendChar(char c);
		void appendIndex(int index);
		bool hasVisited(int index);
		std::string prefix;
		std::set<int> trail;
		int currentIndex;
};

#endif
