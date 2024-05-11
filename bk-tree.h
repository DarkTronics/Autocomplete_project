
#ifndef BKTREE_H
#define BKTREE_H

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
typedef pair<int, string> result;

class BKTree
{
public:
    BKTree();
    ~BKTree();
    void insert(const string &w, int key);
    void suggestTop(const string &w, int t);
    void suggestTopN(const string &w, int t, int num_suggestions);

private:
    struct BKTreeNode
    {
        string word;
        int key;
        int dist;
        BKTreeNode* leftChild = nullptr;
        BKTreeNode* rightSibling = nullptr;
        BKTreeNode(std::string _word, int _key, int _dist) : word(_word), key(_key), dist(_dist) {}
    };

    BKTreeNode* root;
    int min(int a, int b, int c);
    int levenshteinDistance(const string &w1, const string &w2);
    void suggestHelper(BKTreeNode* node, vector<priority_queue<result,vector<result>,greater<result>>*>& suggestions, int num_suggestions, const string &w,
                         int t, bool& isWord);
    void printNSuggestions(priority_queue<result,vector<result>,greater<result>> *suggestions, bool isWord, int &num_to_print);
    void freeEverything(BKTreeNode* node);
};

#endif /* BKTree_h */