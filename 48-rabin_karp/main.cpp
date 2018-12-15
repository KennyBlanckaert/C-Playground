#include <stdlib.h>
#include <stdio.h>

#include "rabin_karp.h"

int main(int argc, char** argv) {

    string input = "defdef";
    string filename = "file.txt";

    Rabin_Karp bm(filename, input, input.length());
    int occurences = bm.start();

    cout << "Found the word \"" << input << "\" " << occurences << " times.";
 
    return 0;
}