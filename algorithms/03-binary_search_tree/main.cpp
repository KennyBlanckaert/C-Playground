#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "tree.h"

using namespace std;

int main() {
    
    vector<int> keys = {50, 40, 30, 45, 35, 55, 60, 51};
    Tree<int> tree(keys);

    tree.draw("tree.dot");

    return 0;
}
