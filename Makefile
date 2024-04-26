TARFILE = ../final_project_cs375.tar
ZIPFILE = $(TARFILE).gz
DIR = ..
FLAGS = -Wall -ggdb -Wextra -pedantic
CC = g++
OBJ = obj
EXE = trie_test

all:

test: $(EXE)
	./$(EXE) < input3.txt > output.txt

$(EXE): $(OBJ)/Trie.o $(OBJ)/main.o 
	$(CC) $(FLAGS) $(OBJ)/main.o $(OBJ)/Trie.o -o $@

$(OBJ)/Trie.o: Trie.cpp Trie.h
	$(CC) $(FLAGS) -c Trie.cpp -o $@

$(OBJ)/main.o: main.cpp Trie.h
	$(CC) $(FLAGS) -c main.cpp -o $@

tar: clean
	tar cvvf $(TARFILE) $(DIR)
	gzip $(TARFILE)

clean:
	rm -f $(EXE)
	rm -f $(OBJ)/*.o
	rm -f output.txt