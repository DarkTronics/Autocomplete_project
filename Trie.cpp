#include "Trie.h"

using namespace std;

Trie::Trie() {
    head = new Node();
}

Trie::~Trie() {
    freeEverything(head);
}

void Trie::insert(const string &word, int num)
{
    Node *temp = head;
    int i = 0;
    while(word[i] != '\0')
    {
        const auto &next = temp->children.find(word[i]);
        Node *node;

        if (temp->favorite == -1 || num > temp->favoritekey) 
        {
            temp->favorite = word[i];
            temp->favoritekey = num;
        }
        
        if(next == temp->children.end())
        {
            node = new Node();
            temp->children[word[i]] = node;
            temp = node;
        } else {
            temp = next->second;
        }
        
        i++;
    }
    temp->key = num > temp->key ? num : temp->key; // handle duplicates
    temp->isWord = true;
}

void Trie::suggest(char pref[20]) {
    Node *temp = head;
    int it = 0;
    while(pref[it] != '\0')
    {
        const auto &next = temp->children.find(pref[it]);
        if(next == temp->children.end()) return;
        temp = next->second;
        it++;
    }
    favorite(temp, pref);
}

void Trie::search(char pref[20]) {
    Node *temp = head;
    int it = 0;
    while(pref[it] != '\0')
    {
        const auto &next = temp->children.find(pref[it]);
        if(next == temp->children.end()) return;
        temp = next->second;
        it++;
    }
    traverse(temp, pref, 1, true);
}

void Trie::topN(char pref[20], unsigned int n) {
    Node *temp = head;
    int it = 0;
    while(pref[it] != '\0')
    {
        const auto &next = temp->children.find(pref[it]);
        if(next == temp->children.end()) return;
        temp = next->second;
        it++;
    }
    clearQueue();
    traverse(temp, pref, n, false);
    topNHelper();
}

void Trie::favorite(Node* node, string prefix) {
    
    char f = node->favorite;
    if (node->isWord && (f == -1 || node->key >= node->favoritekey)) {
        cout << "\"" << prefix << "\" " << node->key << endl;
        return;
    }
    if (f != -1) favorite(node->children[f], prefix + char(f));
}

void Trie::traverse(Node* node, string prefix, unsigned int n, bool print)
{   
    if(node->isWord){
        if (print) cout << endl << "\"" << prefix << "\" " << node->key;
        if(topNsuggestions.size() < n){
            topNsuggestions.push(make_pair(node->key, prefix));
        }
        else if(topNsuggestions.top().first < node->key){
            topNsuggestions.pop();
            topNsuggestions.push(make_pair(node->key, prefix));
        }
    }
    for (const auto &it : node->children) {
        traverse(node->children[it.first], prefix + char(it.first), n, print);
    }
}

void Trie::topNHelper() {
    if (!topNsuggestions.empty()) {
        pair<int, string> temp = topNsuggestions.top();
        topNsuggestions.pop();
        topNHelper();
        cout << "\"" << temp.second << "\" " << temp.first << " ";
        cout << endl;
    }  
}

void Trie::clearQueue() {
    while (!topNsuggestions.empty()) {
        topNsuggestions.pop();
    }
}

void Trie::freeEverything(Node* node)
{
    for (const auto &it : node->children) {
        freeEverything(node->children[it.first]);
    }
    delete node;
}
