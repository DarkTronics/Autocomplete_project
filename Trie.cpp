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
    while(word[it] >= 'a' && word[it] <= 'z')
    {
        int letter_index = word[it] - 'a';
        if (temp->favorite == -1 || num > temp->children[temp->favorite]->key) temp->favorite = letter_index;
        Node *next = temp->children[letter_index];
        if(!next)
        {
            next = new Node();
            temp->children[letter_index] = next;
        }
        temp = next;
        if (num > temp->key) temp->key = num;
        //word[it] = '\0';
        it++;
    }
    if(temp->key < num) temp->key = num;
    temp->isWord = true;
}

void Trie::suggest(char pref[20]) {
    Node *temp = head;
    int it = 0;
    while(pref[it] >= 'a' && pref[it] <= 'z')
    {
        Node *next = temp->children[pref[it]-'a'];
        if(!next) return;
        temp = next;
        it++;
    }
    favorite(temp, pref);
}

// eventually this should just output the TOP word, not all in traversal
void Trie::search(char pref[20]) {
    Node *temp = head;
    int it = 0;
    while(pref[it] >= 'a' && pref[it] <= 'z')
    {
        Node *next = temp->children[pref[it]-'a'];
        if(!next) return;
        temp = next;
        it++;
    }
    traverse(temp, pref);
}

void Trie::favorite(Node* node, string prefix) {
    if(node->isWord) cout << "\"" << prefix << "\" " << node->key << endl;
    char f = node->favorite;
    if (f != -1) {
        favorite(node->children[f], prefix + char(f + 'a'));
    }
}

void Trie::traverse(Node* node, string prefix)
{
    //if(node->isWord) 
    cout << "\"" << prefix << "\" " << node->key << endl;
    for(int i = 0; i < 26; i++)
    {
        if(node->children[i])
        {
            traverse(node->children[i], prefix + char(i + 'a'));
        }
    }
}

void Trie::freeEverything(Node* node)
{
    int i;
    for(i = 0; i < 26; i++)
    {
       if(node->children[i] != nullptr)
       {
        freeEverything(node->children[i]);
       }
    }
    delete node;
}
