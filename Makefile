All:
	g++ -g Trie.cpp -o submission -Wall -Wextra -pedantic

clean:
	rm -f submission
	rm -f trie-results.txt