#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "trie.h"

int main(int argc, char** argv) {
    
    Trie trie;

    trie.add("car");
    trie.add("apple");
    trie.add("cat");
    trie.add("carrot");
    trie.add("cow");

    trie.draw("trie.dot");
    
    return 0;
}