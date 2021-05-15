#include <fstream>
#include <iostream>
#include <set>
#include <stdlib.h>
#include <string>
#include "boggle_board.h"
#include "boggle_trie.h"

using namespace std;

void printUsage(char *path);

int main(int argc, char **argv)
{
	//defaults
	int initWidth = 5;
	int initHeight = 5;
	std::string dictionaryPath("dictionary.txt");
	std::string letters("");

	switch (argc)
	{
		case 1: //nothing supplied, use defaults
			break;
		case 3: //only dimensions supplied
			initWidth = strtol(argv[1], NULL, 10);
			initHeight = strtol(argv[2], NULL, 10);
			break;
		case 4: //dimensions and dictionary supplied
			initWidth = strtol(argv[1], NULL, 10);
			initHeight = strtol(argv[2], NULL, 10);
			dictionaryPath = argv[3];
			break;
		case 5: //dimensions, letters and dictionary supplied
			initWidth = strtol(argv[1], NULL, 10);
			initHeight = strtol(argv[2], NULL, 10);
			dictionaryPath = argv[3];
			letters = argv[4];
			break;
		default:
			printUsage(argv[0]);
			return 1;
	}

	BoggleTrie trie;

	std::string inString;
	std::ifstream inFile(dictionaryPath.c_str());

	if (letters.length() > 0 && letters.length() != (unsigned int)(initWidth * initHeight))
	{
		std::cout << "Letters / dimensions mismatch!" << endl;
		std::cout << "Needed " << initWidth * initHeight << " letters, but got " << letters.length() << std::endl;
		return 1;
	}

	if (inFile.fail())
	{
		std::cout << "failed to open dictionary: " << dictionaryPath << std::endl;
		return 1;
	}

	//populate the dictionary
	while (getline(inFile, inString))
	{
		char lastChar = inString[inString.length() - 1];

		if (lastChar == '\n' || lastChar == '\r')
		{
			//trim the strings of line feed / carriage return
			inString = inString.substr(0, inString.length() - 1);
		}

		trie.addWord(&inString);
	}

	//create a new board and a word list to collect matches
	BoggleBoard board(initWidth, initHeight, &letters);
	std::set<std::string> wordList;

	board.print();
	board.populateWordList(&wordList, &trie);

	std::cout << std::endl << "printing matches:" << std::endl;
	for (std::set<std::string>::iterator sIterator = wordList.begin(); sIterator != wordList.end(); ++sIterator)
	{
		std::cout << *sIterator << std::endl;
	} 

	std::cout << std::endl << "found " << wordList.size() << " matches." << std::endl;

	return 0;
}

void printUsage(char *path)
{
	cout << "Usage: " << path << " W(int) H(int) [letters] [path to dictionary]" << endl;
	cout << "Example: " << path << " 3 3 dictionary.txt abcdefghi" << endl;
	cout << "\tCreates a 3x3 board with the letters abcdefghi and uses dictionary.txt for matches" << endl;
	cout << "\tThe letter list and dictionary path are optional. If not supplied, the board will be randomized and the dictionary will use dictionary.txt" << std::endl;
}
