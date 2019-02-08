#include <stdlib.h>
#include <stdio.h>

#include "boyer_moore.h"

int main(int argc, char** argv) {

    string input = "defdef";
    // cout << "Enter word to search: " << endl;
    // cin >> input;

    string filename = "file.txt";

    Boyer_Moore bm(filename, (uchar*) input.c_str(), input.length());
    int occurences = bm.start();

    cout << "Found the word \"" << input << "\" " << occurences << " times.";

    return 0;
}