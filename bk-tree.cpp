#include "bk-tree.h"

BKTree::BKTree() { 
    root = nullptr; 
}

BKTree::~BKTree() { 
    freeEverything(root); 
}

void BKTree::insert(const string &w, int key) {
    if (root == nullptr) {
        root = new BKTreeNode(w, key, -1);
        return;
    }
    
    BKTreeNode* curNode = root;
    BKTreeNode* child;
    BKTreeNode* newChild;
    int dist;
    
    while (1) {
        dist = levenshteinDistance(curNode->word, w);
        if (!dist)
            return;
        child = curNode->leftChild;
        while (child) {
            if (child->dist == dist) {
                curNode = child;
                break;
            }
            child = child->rightSibling;
        }
        if (!child) {
            newChild = new BKTreeNode(w, key, dist);
            newChild->rightSibling = curNode->leftChild;
            curNode->leftChild = newChild;
            break;
        }
    }
}

void BKTree::suggestTop(const string &w, int t) {
    suggestTopN(w, t, 1);
}

void BKTree::suggestTopN(const string &w, int t, int num_suggestions) {
    vector<priority_queue<result,vector<result>,greater<result>>*> suggestions;
    for (int i = 0; i < t; i++) suggestions.push_back(new priority_queue<result,vector<result>,greater<result>>());
    bool isWord = false;
    
    suggestHelper(root, suggestions, num_suggestions, w, t, isWord);
    int num_to_print = num_suggestions;
    for (int i = 0; i < t; i++) printNSuggestions(suggestions[i], isWord, num_to_print);
}

void BKTree::suggestHelper(BKTreeNode* currNode, vector<priority_queue<result,vector<result>,greater<result>>*>& suggestions, int num_suggestions, const string &w, int t, bool& isWord) {
    int curr_distance = levenshteinDistance(currNode->word, w);
    int min_distance = curr_distance - t;
    int max_distance = curr_distance + t;
    
    if (!curr_distance) {
        isWord = true;
        return;
    }

    curr_distance--;
    if (curr_distance < t) {
        if (suggestions[curr_distance]->size() < num_suggestions) {
            suggestions[curr_distance]->push(make_pair(currNode->key, currNode->word));
        } else if(suggestions[curr_distance]->top().first < currNode->key) {
            suggestions[curr_distance]->pop();
            suggestions[curr_distance]->push(make_pair(currNode->key, currNode->word));
        }
    }
    
    BKTreeNode* child = currNode->leftChild;
    if (!child) return;
    
    while (child) {
        if (min_distance <= child->dist && child->dist <= max_distance)
            suggestHelper(child, suggestions, num_suggestions, w, t, isWord);
        
        child = child->rightSibling;
    }
    
}

void BKTree::printNSuggestions(priority_queue<result,vector<result>,greater<result>> *suggestions, bool isWord, int &num_to_print)
{
    if (isWord) {
        cout << "Word exists." << endl;
        return;
    } else if (num_to_print != 0 && !suggestions->empty()) {
        num_to_print--;
        pair<int, string> temp = suggestions->top();
        suggestions->pop();
        printNSuggestions(suggestions, isWord, num_to_print);
        cout << temp.second << " " << temp.first << endl;
    }
}

int BKTree::levenshteinDistance(const string &w1, const string &w2) {

    if (w1.length() == 0) return w2.length();
    if (w2.length() == 0) return w1.length();
    
    int n_w1 = w1.length();
    int n_w2 = w2.length();
    int cost;
    
    int d[n_w1 + 1][n_w2 + 1];
    
    for (int i = 0; i <= n_w1; i++) d[i][0] = i;
    for (int i = 0; i <= n_w2; i++) d[0][i] = i;
    for (int i = 1; i <= n_w1; i++) {
        for (int j = 1; j <= n_w2; j++) {
            cost = (w1[i - 1] == w2[j - 1]) ? 0 : 1;
            d[i][j] = min(d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost);
        }
    }
    return d[n_w1][n_w2];
}

int BKTree::min(int a, int b, int c) {
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

void BKTree::freeEverything(BKTreeNode* node) {
    if (node) {
        freeEverything(node->leftChild);
        freeEverything(node->rightSibling);
        if (node) delete node;
    }  
}
