TARFILE = ../final_project_cs375.tar
ZIPFILE = $(TARFILE).gz
DIR = ..
FLAGS = -Wall -ggdb -Wextra -pedantic
CC = g++
OBJ = obj

all: test-trie test-bktree test-both

test: test-bktree test-trie test-both
	./test-bktree
	./test-trie
	./test-both

test-both: $(OBJ)/bk-tree.o $(OBJ)/Trie.o $(OBJ)/test-both.o 
	$(CC) $(FLAGS) $(OBJ)/test-both.o $(OBJ)/bk-tree.o $(OBJ)/Trie.o -o $@

test-bktree: $(OBJ)/bk-tree.o $(OBJ)/test-bktree.o 
	$(CC) $(FLAGS) $(OBJ)/test-bktree.o $(OBJ)/bk-tree.o -o $@

test-trie: $(OBJ)/Trie.o $(OBJ)/test-trie.o 
	$(CC) $(FLAGS) $(OBJ)/test-trie.o $(OBJ)/Trie.o -o $@

$(OBJ)/test-both.o: test-both.cpp bk-tree.h Trie.h
	$(CC) $(FLAGS) -c test-both.cpp -o $@

$(OBJ)/bk-tree.o: bk-tree.cpp bk-tree.h
	$(CC) $(FLAGS) -c bk-tree.cpp -o $@

$(OBJ)/test-bktree.o: test-bktree.cpp bk-tree.h
	$(CC) $(FLAGS) -c test-bktree.cpp -o $@

$(OBJ)/Trie.o: Trie.cpp Trie.h
	$(CC) $(FLAGS) -c Trie.cpp -o $@

$(OBJ)/test-trie.o: test-trie.cpp Trie.h
	$(CC) $(FLAGS) -c test-trie.cpp -o $@

tar: clean
	tar cvvf $(TARFILE) $(DIR)
	gzip $(TARFILE)

clean:
	rm -f test-bktree test-trie test-both
	rm -f $(OBJ)/*.o
	rm -f output-bktree.txt output-trie.txt output-both.txt