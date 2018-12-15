#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <queue>
#include <cstring>
#include <fstream>

using namespace std;

#include "knuth_morris_pratt.h"

int main(int argc, char** argv) {

    string input = "abc";
    // cout << "Enter word to search: " << endl;
    // cin >> input;

    string filename = "file.txt";

    KnuthMorrisPratt kmp(filename, (uchar*) input.c_str(), input.length());
    int occurences = kmp.start();

    cout << "Found the word \"" << input << "\" " << occurences << " times.";

    return 0;
}