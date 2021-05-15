#ifndef BOGGLE_BOARD_H
#define BOGGLE_BOARD_H

#include <set>
#include <string>
#include <set>
#include "boggle_trie.h"

class BoggleBoard
{
	public:
		BoggleBoard(int width, int height, std::string *letters);
		~BoggleBoard();
		void print();
		void populateWordList(std::set<std::string> *wordList, BoggleTrie *dictionary);
	private:
		void getPosFromIndex(int index, int *posX, int *posY);
		int getIndexFromPos(int posX, int posY);
		void randomizeBoard();
		void populateBoard(std::string *letters);
		bool inBounds(int x, int y);
		int _width;
		int _height;
		char **board;
};

#endif
