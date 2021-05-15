#ifndef BOGGLE_TRI_H
#define BOGGLE_TRI_H

#include "boggle_trie_node.h"

enum
{
	CONTAINS_WORD = 1 << 0,
	CONTAINS_PREFIX = 1 << 1,
	NOT_IN_TRIE = 1 << 2,
};

class BoggleTrie
{
	public:
		BoggleTrie();
		int checkWord(std::string *word);	
		void addWord(std::string *word);
	private:
		BoggleTrieNode root;
};

#endif
