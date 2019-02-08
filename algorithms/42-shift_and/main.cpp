#include <queue>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

#include "shiftand.h"

int main(int argc, char** argv) {

    // Parameters
    string word = "where";
    string filename = "shakespeare_limited.txt";

    // Needle variables
    const uchar* needle = (uchar*) word.c_str();
    uint needle_length = word.length();

    // Initializing shiftand instance
    Shiftand shiftand(needle, word.length());

    // Parsing file to string
    ifstream in(filename);
    string contents((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

    // Execute SHIFT-AND
    queue<const uchar*> results;
    int occurences = shiftand.search(results, (const uchar*) contents.c_str(), contents.length());

    cout << "I found \"" << word << "\" " << occurences << " times in your file!" << endl;

    return 0;
}