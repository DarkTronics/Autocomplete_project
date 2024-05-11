#include "bk-tree.h"

BKTree::BKTree() { 
    root = nullptr; 
}

BKTree::~BKTree() { 
    freeEverything(root); 
}

void BKTree::insert(const string &word, int key) {
    if (root == nullptr) {
        root = new BKTreeNode(word, key, -1);
        return;
    }
    
    BKTreeNode* currNode = root;
    BKTreeNode* child;
    BKTreeNode* newChild;
    int dist;
    while (1) {
        dist = levenshteinDistance(currNode->word, word);
        if (!dist)
            return;
        child = currNode->leftChild;
        while (child) {
            if (child->dist == dist) {
                currNode = child;
                break;
            }
            child = child->rightSibling;
        }
        if (!child) {
            newChild = new BKTreeNode(word, key, dist);
            newChild->rightSibling = currNode->leftChild;
            currNode->leftChild = newChild;
            break;
        }
    }
}

string BKTree::suggestTop(const string &word, int max_distance) {
    suggestTopN(word, max_distance, 1);
    return top;
}

void BKTree::suggestTopN(const string &word, int max_distance, unsigned int num_suggestions) {
    vector<priority_queue<result,vector<result>,greater<result>>*> suggestions;
    for (int i = 0; i <= max_distance; i++) suggestions.push_back(new priority_queue<result,vector<result>,greater<result>>());
    
    suggestHelper(root, suggestions, num_suggestions, word, max_distance);
    int num_to_print = num_suggestions;
    for (int i = 0; i <= max_distance; i++) printNSuggestions(suggestions[i], num_to_print);
}
int n = 0;
void BKTree::suggestHelper(BKTreeNode* currNode, vector<priority_queue<result,vector<result>,greater<result>>*>& suggestions, unsigned int num_suggestions, const string &word, int max_distance) {
    int curr_distance = levenshteinDistance(currNode->word, word);
    int lower_limit = curr_distance - max_distance;
    int upper_limit = curr_distance + max_distance;
    n++;
    if (curr_distance <= max_distance) {
        if (suggestions[curr_distance]->size() < num_suggestions) {
            suggestions[curr_distance]->push(make_pair(currNode->key, currNode->word));
        } else if (suggestions[curr_distance]->top().first < currNode->key) {
            suggestions[curr_distance]->pop();
            suggestions[curr_distance]->push(make_pair(currNode->key, currNode->word));
        }
    }
    
    BKTreeNode* child = currNode->leftChild;
    if (!child) return;
    
    while (child) {
        if (lower_limit <= child->dist && child->dist <= upper_limit)
            suggestHelper(child, suggestions, num_suggestions, word, max_distance);
        
        child = child->rightSibling;
    }
    
}

void BKTree::printNSuggestions(priority_queue<result,vector<result>,greater<result>> *suggestions, int &num_to_print)
{
    if (!suggestions->empty()) {
        
        pair<int, string> temp = suggestions->top();
        suggestions->pop();
        printNSuggestions(suggestions, num_to_print);
        num_to_print--;
        if (num_to_print >= 0) {
            cout << "\"" << temp.second << "\"" << " " << temp.first << endl;
            top = temp.second;
            cout << n << " nodes visited" << endl;
        }
    }
}

int BKTree::levenshteinDistance(const string &word1, const string &word2) {

    if (word1.length() == 0) return word2.length();
    if (word2.length() == 0) return word1.length();
    
    int n_word1 = word1.length();
    int n_word2 = word2.length();
    int cost;
    
    int d[n_word1 + 1][n_word2 + 1];
    for (int i = 0; i <= n_word1; i++) d[i][0] = i;
    for (int i = 0; i <= n_word2; i++) d[0][i] = i;

    for (int i = 1; i <= n_word1; i++) {
        for (int j = 1; j <= n_word2; j++) {
            cost = (word1[i - 1] == word2[j - 1]) ? 0 : 1;
            d[i][j] = min(d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost);
        }
    }
    return d[n_word1][n_word2];
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
