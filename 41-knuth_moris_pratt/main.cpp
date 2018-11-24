#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "knuth_morris_pratt.h"

using namespace std;

int main(int argc, char** argv) {

    string input = "art";
    // cout << "Enter word to search: " << endl;
    // cin >> input;

    string filename = "shakespeare_limited.txt";

    KnuthMorrisPratt kmp(filename, input.c_str(), input.length());
    int occurences = kmp.start();

    cout << "Found the word \"" << input << "\" " << occurences << " times.";

    return 0;
}