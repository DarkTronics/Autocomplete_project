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
        Node *next = temp->children[word[it]-'a'];
        if(!next)
        {
            next = new Node();
            temp->children[word[it]-'a'] = next;
        }
        temp = next;
        //word[it] = '\0';
        it++;
    }
    if(temp->key < num) temp->key = num;
    else if(temp->key == -1) temp->key = num;
    temp->isWord = true;
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

void Trie::traverse(Node* node, string prefix)
{
    if(node->isWord) cout << "\"" << prefix << "\" " << node->key << endl;
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
