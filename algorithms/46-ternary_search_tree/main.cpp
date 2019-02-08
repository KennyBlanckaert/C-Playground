#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "ternary_search_tree.h"

int main(int argc, char** argv) {
    
    Ternary_Search_Tree ternary_search_tree;

    ternary_search_tree.add("car");
    ternary_search_tree.add("apple");
    ternary_search_tree.add("cat");
    ternary_search_tree.add("carrot");
    ternary_search_tree.add("cow");

    ternary_search_tree.draw("ternary_search_tree.dot");
    
    return 0;
}