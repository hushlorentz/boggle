#include "boggle_trie.h"
#include "boggle_trie_node.h"

#include <ctype.h>
#include <iostream>

//each trie node has 26 children, one for each letter.
//if a tested child is non-NULL, then we know the corresponding letter exists in the trie and the prefix is valid.
//if the prefix is valid and the node is a termination point, we know the word is valid.
BoggleTrieNode::BoggleTrieNode()
{
	isTerminationPoint = false;

	for (int i = 0; i < 26; i++)
	{
		children[i] = 0;
	}
}

void BoggleTrieNode::addWord(std::string *s)
{
	int index = charToIndex((*s)[0]);

	if (children[index] == 0)
	{
		children[index] = new BoggleTrieNode();
	}

	std::string sub = s->substr(1, s->length());

	if (sub.length() > 0)
	{
		children[index]->addWord(&sub);
	}
	else
	{
		children[index]->isTerminationPoint = true;
	}
}

int BoggleTrieNode::findWord(std::string *s)
{
	int index = charToIndex((*s)[0]);

	if (children[index] == 0)
	{
		return NOT_IN_TRIE;
	}
	else
	{
		if (s->length() == 1)
		{
			int retValue = CONTAINS_PREFIX;

			if (children[index]->isTerminationPoint)
			{
				retValue |= CONTAINS_WORD;
			}

			return retValue;
		}
		else
		{
			std::string sub = s->substr(1, s->length());
			return children[index]->findWord(&sub);
		}
	}
}

int BoggleTrieNode::charToIndex(char c)
{
	return toupper(c) - 'A';
}

BoggleTrieNode::~BoggleTrieNode()
{
	for (int i = 0; i < 26; i++)
	{
		if (children[i] != 0)
		{
			delete children[i];
		}
	}
}
