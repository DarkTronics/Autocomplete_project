#include <iostream>
#include <fstream>
#include <chrono>
#include "Trie.h"

using namespace std;

// Capital letters are excluded from the Trie
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
    //fills in Trie form input file
    std::ifstream myfile; myfile.open("input2.txt");
    Trie trie;
    string s;
    int i;
    while (!myfile.eof()) {
        myfile >> s >> i;
        trie.insert(s, i);
    }
    myfile.close();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tree_build_time = end - start;

    char lines[35] = "+===============================+\n";
    char query[20];
    int num_suggestions;
    cout << endl << lines << "TRIE TEST" << endl << lines;
    cout << "Input QUERY: ";
    cin >> query;
    cout << "Number of suggestions: ";
    cin >> num_suggestions;
    
    //opens output file and redirects it to cout
    ofstream fileOut("output-trie.txt");
    cout.rdbuf(fileOut.rdbuf()); 

    cout << lines << "QUERY: " << query << endl;
    cout << lines << "TOP SUGGESTION:" << endl;
    start = std::chrono::high_resolution_clock::now();
    trie.suggestTop(toLower(query));
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> suggest_time = end - start;

    cout << lines << "TOP " << num_suggestions << " SUGGESTIONS:" << endl;
    start = std::chrono::high_resolution_clock::now();
    trie.suggestTopN(toLower(query), num_suggestions);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> topN_time = end - start;

    cout << lines << "FULL TRAVERSAL:";
    start = std::chrono::high_resolution_clock::now();
    trie.search(toLower(query));
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> traversal_time = end - start;

    
    cout << endl << lines;
    cout << "TREE BUILD TIME:      " << tree_build_time.count() << " ms" << endl;
    cout << "SUGGEST ONE TIME:     " << suggest_time.count() << " ms" << endl;
    cout << "SUGGEST N TIME:       " << topN_time.count() << " ms" << endl;
    cout << "TRAVERSAL TIME:       " << traversal_time.count() << " ms" << endl << lines;

    return 0;
    
}
/*
// to get rid of duplicates
#include <unordered_set>
int main() {
    std::ifstream myfile; myfile.open("input2.txt");
    unordered_set<string> set;
    string s;
    int i;
    ofstream fileOut("input1.txt");
    cout.rdbuf(fileOut.rdbuf()); 
    int num_omitted = 0;
    while (!myfile.eof()) {
        
        myfile >> s >> i;
        if (set.find(s) == set.end()) {
            
            set.insert(s);
        } else {
            cout << s << " " << i << endl;
            num_omitted++;
        }
    }
    cout << num_omitted;
    myfile.close();

    // this is code to parse the dictionary i downloaded from the internet
    // https://martinweisser.org/corpora_site/word_lists.html
    std::string word;
    int frequency;

    // Ignore the header line
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Read and output only the desired columns
    while (std::cin >> frequency) {
        // Skip other columns until we reach the frequency
        
        // Read the frequency
        std::cin >> word;

        for (int i = 0; i < 2; ++i) {
            std::string temp;
            std::cin >> temp;
        }

        // Output word and frequency
        std::cout << word << " " << frequency << std::endl;
    }
    
    return 0;
}
*/