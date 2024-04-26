#include <iostream>
#include <chrono>
#include "Trie.h"

using namespace std;

int main() {
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    
    Trie trie;
    while (!cin.eof()) {
        string s;
        int i;
        cin >> s >> i;
        trie.insert(s, i);
    }
    
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tree_build_time = end - start;
    
    char query[20] = "hur";
    char lines[32] = "+============================+\n";

  
    
    cout << lines << "QUERY: " << query << endl;
    cout << lines << "TOP SUGGESTION:" << endl;
    start = std::chrono::high_resolution_clock::now();
    trie.suggest(query);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> suggest_time = end - start;
    cout << lines << "FULL TRAVERSAL:" << endl;
    start = std::chrono::high_resolution_clock::now();
    trie.search(query);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> traversal_time = end - start;
    cout << lines;
    
    cout << "TREE BUILD TIME:  " << tree_build_time.count() << " ms" << endl;
    cout << "SUGGEST TIME:     " << suggest_time.count() << " ms" << endl;
    cout << "TRAVERSAL TIME:   " << traversal_time.count() << " ms" << endl << lines;

    return 0;
}