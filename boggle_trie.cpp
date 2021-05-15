#include <iostream>
#include "boggle_trie.h"

BoggleTrie::BoggleTrie()
{
}

void BoggleTrie::addWord(std::string *s)
{
	root.addWord(s);
}

int BoggleTrie::checkWord(std::string *p)
{
	return root.findWord(p);
}
