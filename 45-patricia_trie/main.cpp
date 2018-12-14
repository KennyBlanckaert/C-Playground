#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "patricia_patricia_tree.h"

int main(int argc, char** argv) {
    
    Patricia_Tree patricia_tree;

    patricia_tree.add("car");
    patricia_tree.add("apple");
    patricia_tree.add("cat");
    patricia_tree.add("carrot");
    patricia_tree.add("cow");

    patricia_tree.draw("patricia_tree.dot");
    
    return 0;
}