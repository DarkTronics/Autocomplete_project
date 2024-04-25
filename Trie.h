#include <string>
#include <iostream>

using namespace std;

class Trie {
public:
    
    Trie();
    ~Trie();
    void insert(const string &word, int num);
    void suggest(char word[20]);
    void search(char word[20]);

private:
    struct Node
    {
        int key = -1;
        bool isWord = false;
        char favorite = -1; // index of the child with the highest key
        Node* children[26];
        Node() {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
    };

    Node *head;
    void favorite(Node* node, string prefix);
    void traverse(Node *node, string prefix);
    void freeEverything(Node *node);
};