#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;
typedef pair<int, string> result;

class Trie {
public:
    
    Trie();
    ~Trie();
    void insert(const string &word, int num);
    void search(char word[20]);
    void suggestTop(char word[20]);
    void suggestTopN(char pref[20], unsigned int n);

private:
    struct Node
    {
        int key = -1;
        bool isWord = false;
        char favorite = -1; // index of the child with the highest key
        int favoritekey = -1;
        unordered_map<char, Node*> children;
    };

    priority_queue<result,vector<result>,greater<result>> topNsuggestions;
    Node *head;
    void favorite(Node* node, string prefix);
    void traverse(Node *node, string prefix, unsigned int n, bool print);
    void topNHelper();
    void freeEverything(Node *node);
};
