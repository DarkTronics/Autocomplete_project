#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ostream>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

struct Trie
{
    public:
    bool isWord;
    int key;
    Trie* children[95];
};

Trie *newTrie() //create new node
{
    Trie *node = new Trie;
    node->key = -1;
    node->isWord = false;
    for(int i = 0; i < 95; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

void insert(Trie* node, char word[20], int num)
{
    Trie *temp = node;
    int it = 0;
    while(word[it] >= 32 && word[it] <= 126)
    {
        if(!temp->children[word[it]-' '])
        {
            temp->children[word[it]-' '] = newTrie();
        }
        temp = temp->children[word[it]-' '];
        word[it] = '\0';
        it++;
    }
    if(temp->key < num)
    {
        temp->key = num;
    }
    else if(temp->key == -1)
    {
        temp->key = num;
    }
    temp->isWord = true;
}

void traverse(Trie* node, string prefix, ofstream &filename)
{
    if(node->isWord)
    {
        filename << "\"" << prefix << "\" " << node->key << endl;
    }
    for(int i = 0; i < 95; i++)
    {
        if(node->children[i])
        {
            traverse(node->children[i], prefix + char(i + 32), filename);
        }
    }
}

void freeEverything(Trie* node)
{
    int i;
    for(i = 0; i < 95; i++)
    {
       if(node->children[i] != NULL)
       {
        freeEverything(node->children[i]);
       }
    }
    delete node;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
	{
		printf("Usage: ./exe <input_file>\n");
		return -1;
	}

    int file = open(argv[1], O_RDWR);
    struct stat sb;
    fstat(file, &sb);
    if(file == -1)
    {
        printf("Error opening file\n");
        return(1);
    }

    char *map = (char*)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, file, 0); // mmap to map

    Trie* root = newTrie();

    int lastQuotationIndex = 0;
    int firstQuotationIndex = 0;
    int firstDigitIndex = 0;
    int lastDigitIndex = 0;
    int leftIndex = 0;
    int rightIndex = 0;
    char strarr[50] = {};//string to put into trie
    char strnum[10000] = {};//number to put into trie
    auto start_tp = chrono::steady_clock::now();
    for(int i = 0; i < sb.st_size; i++)
    {
        if(map[i] == '\n' || i == sb.st_size-1) //one line starting from left index to right index
        {
            for(int j = i; j > leftIndex; j--)// find last quotation index
            {
                if(map[j] == '\"')
                {
                    lastQuotationIndex = j;
                    break;
                }
            }
            rightIndex = i-1;
            for(int j = leftIndex; j <= rightIndex; j++)// find first quotation index
            {
                if(map[j] == '\"')
                {
                    firstQuotationIndex  = j;
                    break;
                }
            }

            int count = 0;
            for(int j = firstQuotationIndex; j <= lastQuotationIndex; j++)//check string error
            {
                if(j > firstQuotationIndex && j < lastQuotationIndex)
                {
                    if(map[j] == '\"' && map[j-1] != '\\')
                    {
                        printf("Wrong \" Error at line ");
                        for(int k = firstQuotationIndex; k <= rightIndex; k++)
                        {
                            printf("%c",map[k]);
                        }
                        printf("\n");
                        freeEverything(root);
                        munmap(map, sb.st_size);
                        return 0;                   
                    }
                }
                if((map[j] == '\\') && (map[j+1] == '.'))
                {
                    printf("Detected (backslash and .) Error at line ");
                    for(int k = firstQuotationIndex; k <= rightIndex; k++)
                    {
                        printf("%c",map[k]);
                    }
                    printf("\n");
                    freeEverything(root);
                    munmap(map, sb.st_size);
                    return 0;
                }
                if((map[j] == '\\') && (map[j+1] != '\\') && (map[j+1] != '\"'))
                {
                    printf("Detected (backslash and quotation or other) Error at line ");
                    for(int k = firstQuotationIndex; k <= rightIndex; k++)
                    {
                        printf("%c",map[k]);
                    }
                    printf("\n");
                    freeEverything(root);
                    munmap(map, sb.st_size);
                    return 0;
                }
                else if((map[j] == '\\' && map[j+1] == '\\') || (map[j] == '\\' && map[j+1] == '\"'))
                {
                    strarr[count] = '\\';
                    //wordToInsert += '\\';
                    count++;
                    j++;
                }
                if((j > firstQuotationIndex) && (j < lastQuotationIndex))
                {
                    strarr[count] = map[j];
                    //wordToInsert += map[j];
                    count++;
                }
            }

            for(int j = rightIndex; j >= lastQuotationIndex; j--)
            {
                if(isdigit(map[j]))
                {
                    lastDigitIndex = j;
                    break;
                }
            }
            for(int j = lastQuotationIndex; j < lastDigitIndex; j++)
            {
                if(isdigit(map[j]) && map[j] != '0')
                {
                    firstDigitIndex = j;
                    break;
                }
            }
            for(int j = firstDigitIndex; j < lastDigitIndex; j++)
            {
                if(!isdigit(map[j]))
                {
                    printf("Detected (missing number or not a number) Error at line ");
                    for(int k = firstQuotationIndex; k <= rightIndex; k++)
                    {
                        printf("%c",map[k]);
                    }
                    printf("\n");
                    freeEverything(root);
                    munmap(map, sb.st_size);
                    return 0;
                }
            }
            int count2 = 0;
            for(int j = lastQuotationIndex+1; j <= rightIndex; j++)// check number error
            {
                if(map[j] == '-' || map[j] == '+' || (!isdigit(map[j]) && map[j] != ' '))  
                {
                     cout << map[j];
                    printf("Detected (- or +) Error at line ");
                    for(int k = firstQuotationIndex; k <= rightIndex; k++)
                    {
                        printf("%c",map[k]);
                    }
                    printf("\n");
                    freeEverything(root);
                    munmap(map, sb.st_size);
                    return 0;
                }
                if(map[j] != ' ' && map[j] != '\"')
                {
                    strnum[count2] = map[j];
                    count2++;
                }
            }
            int count3 = 0;
            int intval = 0;
            while(strnum[count3] >= 48 && strnum[count3] <= 57)
            {
                intval = intval * 10 + (strnum[count3] - '0');
                strnum[count3] = '\0';
                count3++;
            }
            leftIndex = i+1;
            insert(root, strarr, intval);
        }
    }
    auto stop_tp = chrono::steady_clock::now();
    auto duration = chrono::duration<double>(stop_tp - start_tp);
    cout << "Elapsed time: " << duration.count() << endl;
    ofstream output("trie-results.txt");
    traverse(root, "", output);

    freeEverything(root);
    output.close();
    munmap(map, sb.st_size);
    return 0;
}