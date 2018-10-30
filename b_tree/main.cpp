#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "btree.h"

#define NODE_SIZE 4

using namespace std;

void lowercase(string& word) { transform(word.begin(), word.end(), word.begin(), ::tolower); }

int main(int argc, char** argv) {

    // Disk stores BNodes
    // BNode consist of:
    //              a string (word)
    //              a unsigned integer (times added)
    //              KNOOP_SIZE (numsber of keys in node)
    // BTree uses Disk to access BNodes
    // 3 BNodes accesible at a time (crashtest)
    Disk<BNode<string, unsigned int, NODE_SIZE>> disk;
    BTree<string, unsigned int, NODE_SIZE> tree(disk);

    // Open file
    // Read words
    ifstream file("words.txt");

    string word;
    int counter = 0;
    while (file >> word) { 
        lowercase(word);

        // cout << counter << " | " << "\"" << word << "\"";

        int occur = tree.search(word);
        tree.add(word, occur + 1);
        // cout << " (" << (occur+1) << ")" << endl;

        // cout << endl;

        counter++;
    } 

    cout << "Done..." << endl;

    vector<pair<string, unsigned int>> result = tree.getHighestOccurrences();
    for (int i = 0; i < result.size(); i++) {
        cout << result[i].second << " " << result[i].first << endl;
    }

    return 0;
}