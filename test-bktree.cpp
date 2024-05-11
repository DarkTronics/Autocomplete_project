#include <iostream>
#include <fstream>
#include <chrono>
#include "bk-tree.h"

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
    string s;
    int i;
    while (!myfile.eof()) {
        myfile >> s >> i;
        tree.insert(s, i);
    }
    myfile.close();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tree_build_time = end - start;

    char lines[35] = "+===============================+\n";
    char query[20];
    int num_suggestions;
    cout << endl << lines << "BK-TREE TEST" << endl << lines;
    cout << "Input QUERY: ";
    cin >> query;
    cout << "Number of suggestions: ";
    cin >> num_suggestions;
    
    //opens output file and redirects it to cout
    ofstream fileOut("output-bktree.txt");
    cout.rdbuf(fileOut.rdbuf()); 

    cout << lines << "QUERY: " << query << endl;
    cout << lines << "TOP SUGGESTION:" << endl;
    start = std::chrono::high_resolution_clock::now();
    tree.suggestTop(toLower(query), 20);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> suggest_time = end - start;

    cout << lines << "TOP " << num_suggestions << " SUGGESTIONS:" << endl;
    start = std::chrono::high_resolution_clock::now();
    tree.suggestTopN(toLower(query), 20, num_suggestions);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> topN_time = end - start;
    
    cout << endl << lines;
    cout << "TREE BUILD TIME:      " << tree_build_time.count() << " ms" << endl;
    cout << "SUGGEST ONE TIME:     " << suggest_time.count() << " ms" << endl;
    cout << "SUGGEST N TIME:       " << topN_time.count() << " ms" << endl;
   
    return 0;
    
}