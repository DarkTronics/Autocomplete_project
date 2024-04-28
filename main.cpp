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
    std::ifstream myfile; myfile.open("input3.txt");
    Trie trie;
    while (!myfile.eof()) {
        string s;
        int i;
        myfile >> s >> i;
        trie.insert(s, i);
    }
    myfile.close();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tree_build_time = end - start;
    char query[20];
    cout << "Input QUERY: ";
    cin >> query;
    char lines[32] = "+============================+\n";
    //opens output file and redirects it to cout
    ofstream fileOut("output.txt");
    cout.rdbuf(fileOut.rdbuf()); 

    cout << lines << "QUERY: " << query << endl;
    cout << lines << "TOP SUGGESTION:" << endl;
    start = std::chrono::high_resolution_clock::now();
    trie.suggest(toLower(query));
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> suggest_time = end - start;

    cout << lines << "FULL TRAVERSAL:" << endl;
    start = std::chrono::high_resolution_clock::now();
    trie.search(toLower(query));
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> traversal_time = end - start;
    
    cout << lines;
    cout << "TREE BUILD TIME:  " << tree_build_time.count() << " ms" << endl;
    cout << "SUGGEST TIME:     " << suggest_time.count() << " ms" << endl;
    cout << "TRAVERSAL TIME:   " << traversal_time.count() << " ms" << endl << lines;

    return 0;
    
    /*
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
    */
    return 0;
}