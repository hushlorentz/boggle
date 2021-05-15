#include "boggle_board.h"
#include "boggle_node.h"

#include <cstring>
#include <iostream>
#include <queue>
#include <set>

#include <cstdlib>
#include <time.h>

BoggleBoard::BoggleBoard(int width, int height, std::string *letters) : _width(width), _height(height)
{
	board = new char*[_height];

	for (int i = 0; i < _height; i++)
	{
		board[i] = new char[_width];
	}

	if (letters->length() == 0)
	{
		srand(time(NULL));
		randomizeBoard();
	}
	else
	{
		populateBoard(letters);
	}
}

void BoggleBoard::randomizeBoard()
{
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			board[i][j] = 'A' + (rand() % 26);
		}
	}
}

void BoggleBoard::populateBoard(std::string *letters)
{
	int letterIndex = 0;

	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			board[i][j] = toupper((*letters)[letterIndex++]);
		}
	}
}

//use breadth-first search to create all permutations of the boggle board
//discontinue branch if the current prefix is not in the dictionary
//if we reach a termination point in the trie, the word is a match, so add it to the set
void BoggleBoard::populateWordList(std::set<std::string> *wordList, BoggleTrie *dictionary)
{
	std::queue<BoggleNode> checkList;

	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			checkList.push(BoggleNode(board[i][j], getIndexFromPos(j, i)));

			while (!checkList.empty())
			{
				BoggleNode nextNode(checkList.front());	
				checkList.pop();

				int result = dictionary->checkWord(&(nextNode.prefix));

				if ((result & CONTAINS_WORD) == CONTAINS_WORD)
				{
					wordList->insert(nextNode.prefix);
				}
				if ((result & CONTAINS_PREFIX) == CONTAINS_PREFIX)
				{
					int currentPosX = 0;
					int currentPosY = 0;

					getPosFromIndex(nextNode.currentIndex, &currentPosX, &currentPosY);

					//look in all 8 directions
					for (int i = -1; i <= 1; i++)
					{
						for (int j = -1; j <= 1; j++)
						{
							int xDelta = currentPosX + j;
							int yDelta = currentPosY + i;
							int testIndex = getIndexFromPos(xDelta, yDelta);

							if (inBounds(xDelta, yDelta) && !nextNode.hasVisited(testIndex))
							{
								BoggleNode newNode(nextNode);
								newNode.appendChar(board[yDelta][xDelta]);
								newNode.appendIndex(testIndex);
								checkList.push(newNode);
							}
						}
					}
				}
			}
		}
	}
}

//return the x,y location from the boggle tile index
//indices run from 0...width*height
void BoggleBoard::getPosFromIndex(int index, int *posX, int *posY)
{
	*posX = index % _width;
	*posY = index / _width;
}

//create and index from the x,y position of a boggle tile
int BoggleBoard::getIndexFromPos(int posX, int posY)
{
	return posX + posY * _width;
}

//check if the location is within the boggle board
bool BoggleBoard::inBounds(int x, int y)
{
	return x >= 0 && x < _width && y >= 0 && y < _height;
}

void BoggleBoard::print()
{
	std::cout << std::endl << "printing boggle board:" << std::endl << std::endl;

	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			std::cout << board[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

BoggleBoard::~BoggleBoard()
{
	for (int i = 0; i < _height; i++)
	{
		delete [] board[i];
	}

	delete [] board;
}
