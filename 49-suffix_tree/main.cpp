#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "suffix_tree.h"

int main(int argc, char** argv) {
    
    Patricia_Tree patricia_tree;

    patricia_tree.add("banana");

    patricia_tree.draw("suffix_tree.dot");
    
    return 0;
}