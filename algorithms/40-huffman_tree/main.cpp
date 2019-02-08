#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

#include "huffman.h"

int main(int argc, char** argv) {
    
    Huffman_Tree huffman("file.txt");
    huffman.draw("huffman.dot");
    
    return 0;
}