CC = g++
CFLAGS = -Wall
OBJS = boggle_trie.o boggle_board.o boggle_main.o boggle_node.o boggle_trie_node.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o boggle

boggle_main.o: boggle_main.cpp
	$(CC) $(CFLAGS) -c boggle_main.cpp

boggle_trie.o: boggle_trie.h boggle_trie.cpp
	$(CC) $(CFLAGS) -c boggle_trie.cpp

boggle_trie_node.o: boggle_trie_node.h boggle_trie_node.cpp
	$(CC) $(CFLAGS) -c boggle_trie_node.cpp

boggle_board.o: boggle_board.h boggle_board.cpp
	$(CC) $(CFLAGS) -c boggle_board.cpp

boggle_node.o: boggle_node.h boggle_node.cpp	
	$(CC) $(CFLAGS) -c boggle_node.cpp

run: all
	./boggle

clean:
	rm *.o boggle
