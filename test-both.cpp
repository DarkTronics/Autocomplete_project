#include <iostream>
#include <fstream>
#include <chrono>
#include "bk-tree.h"
#include "Trie.h"

using namespace std;

// Capital letters are excluded from the tree
char *toLower(char s[20]) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] += ' ';
        i++;
    }
    return s;
}

int main() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    //fills in tree form input file
    std::ifstream myfile; myfile.open("input2.txt");
    BKTree tree;
    Trie trie;
    string s;
    int i;
    while (!myfile.eof()) {
        myfile >> s >> i;
        tree.insert(s, i);
        trie.insert(s, i);
    }
    myfile.close();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tree_build_time = end - start;

    char lines[35] = "+===============================+\n";
    char query[20];
    cout << endl << lines << "COMBINED TEST" << endl << lines;
    cout << "Input QUERY: ";
    cin >> query;
    
    //opens output file and redirects it to cout
    ofstream fileOut("output-both.txt");
    cout.rdbuf(fileOut.rdbuf()); 

    cout << lines << "QUERY: " << query << endl;
    cout << lines << "TOP SUGGESTION:" << endl;
    start = std::chrono::high_resolution_clock::now();
    trie.suggestTop(&(tree.suggestTop(toLower(query), 20))[0]);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> suggest_time = end - start;
    
    cout << endl << lines;
    cout << "SUGGEST TIME:     " << suggest_time.count() << " ms" << endl;
   
    return 0;
    
}