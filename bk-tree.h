
#ifndef BKTREE_H
#define BKTREE_H

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
typedef pair<int, string> result;

class BKTree
{
public:
    BKTree();
    ~BKTree();
    void insert(const string &word, int priority);
    string suggestTop(const string &word, int max_distance);
    void suggestTopN(const string &word, int max_distance, int unsigned num_suggestions);
    
private:
    struct BKTreeNode
    {
        string word;
        int priority;
        unordered_map<int, BKTreeNode *> children;
        BKTreeNode(std::string _word, int _priority) : word(_word), priority(_priority) {}
    };

    BKTreeNode* root;
    string top;
    int min(int a, int b, int c);
    int levenshteinDistance(const string &word1, const string &word2);
    void traverse(BKTreeNode* node, vector<priority_queue<result,vector<result>,greater<result>>*>& suggestions, unsigned int num_suggestions, const string &word, int max_distance);
    void printNSuggestions(priority_queue<result,vector<result>,greater<result>> *suggestions, int &num_to_print);
    void freeEverything(BKTreeNode* node);
};

#endif /* BKTree_h */