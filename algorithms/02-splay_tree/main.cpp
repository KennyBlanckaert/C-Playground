#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "tree.h"

using namespace std;

int main() {
    
    vector<int> keys = {50, 40, 30, 45, 35, 55, 60, 51};
    Tree<int> splay_tree(keys);

    // Is 51 at the top?
    splay_tree.draw("splay_tree.dot");

    return 0;
}
