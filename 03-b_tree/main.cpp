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

    // disk stores BNodes
    // BNode consist of:
    //              a string (word)
    //              a unsigned integer (times added)
    //              KNOOP_SIZE (numsber of keys in node)
    // BTree uses Disk to access BNodes
    Disk<BNode<string, unsigned int, NODE_SIZE>> disk;
    BTree<string, unsigned int, NODE_SIZE> tree(disk);

    // open file
    // read words
    ifstream file("words.txt");

    string word;
    int counter = 0;
    while (file >> word) { 
        lowercase(word);

        int occur = tree.search(word);
        tree.add(word, occur + 1);

        counter++;
    } 

    // get results and sort
    vector<pair<string, unsigned int>> result = tree.getHighestOccurrences();
    for (int i = 0; i < result.size(); i++) {
        unsigned int hulp_num = result[i].second;
        string hulp_str = result[i].first;
		int j = i - 1;

		while (j >= 0 && hulp_num > result[j].second){
			result[j+1].second = result[j].second;
            result[j+1].first = result[j].first;
			j--;
		}
		result[j+1].second = hulp_num;
        result[j+1].first = hulp_str;
    }

    // print
    for (int i = 0; i < result.size(); i++) {
        cout << result[i].second << " " << result[i].first << endl;
    }

    return 0;
}