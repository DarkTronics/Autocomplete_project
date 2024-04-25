#include <string>
#include <iostream>

using namespace std;

class Trie {
public:
    
    Trie();
    ~Trie();
    void insert(const string &word, int num);
    void search(char word[20]);

private:
    struct Node
    {
        bool isWord = false;
        int key = -1;
        Node* children[26];
        Node() {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
    };

    Node *head;
    void traverse(Node *node, string prefix);
    void freeEverything(Node *node);
};