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
    int it = 0;
    while(word[it] != '\0')
    {
        const auto &next = temp->children.find(word[it]);
        Node *node;

        if (temp->favorite == -1 || num > temp->children[temp->favorite]->key) 
        {
            temp->favorite = word[it];
        }
        
        if(next == temp->children.end())
        {
            node = new Node();
            temp->children[word[it]] = node;
            temp = node;
        } else {
            temp = next->second;
        }
        
        if (num > temp->key) temp->key = num;
        num++; // increment to indicate more successful children
        it++;
    }
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
    traverse(temp, pref, n, false);
    while(!top5suggestions.empty()){
        pair<int, string> temp = top5suggestions.top();
        cout << "\"" << temp.second << "\" " << temp.first << " ";
        top5suggestions.pop();
        cout << endl;
    }
}

void Trie::favorite(Node* node, string prefix) {
    
    char f = node->favorite;
    if (node->isWord && (f == -1 || node->key >= node->children[f]->key)) {
        cout << "\"" << prefix << "\" " << node->key << endl;
        return;
    }
    if (f != -1) favorite(node->children[f], prefix + char(f));
}

void Trie::traverse(Node* node, string prefix, unsigned int n, bool print)
{
    if (print) cout << endl << "\"" << prefix << "\" " << node->key;
    if(node->isWord){
        if (print) cout << " <--- WORD";
        if(top5suggestions.size() < n){
            top5suggestions.push(make_pair(node->key, prefix));
        }
        else if(top5suggestions.top().first < node->key){
            top5suggestions.pop();
            top5suggestions.push(make_pair(node->key, prefix));
        }
    }
    for (const auto &it : node->children) {
        traverse(node->children[it.first], prefix + char(it.first), n, print);
    }
}

void Trie::freeEverything(Node* node)
{
    for (const auto &it : node->children) {
        freeEverything(node->children[it.first]);
    }
    delete node;
}
