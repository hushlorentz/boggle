#ifndef BOGGLE_TRIE_NODE_H
#define BOGGLE_TRIE_NODE_H

#include <string>

class BoggleTrieNode
{
	public:
		BoggleTrieNode();
		~BoggleTrieNode();
		void addWord(std::string *word);
		int findWord(std::string *word);
		bool isTerminationPoint;
	private:
		int charToIndex(char c);
		BoggleTrieNode *children[26];
};

#endif
