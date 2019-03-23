#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

using namespace std;

int main() {
    
    vector<int> keys = {50, 30, 100, 20, 40, 110, 10, 49, 105, 120};
    Tree<int> tree(keys);
    tree.draw("tree.dot");

    tree.breadth_first_search();

    return 0;
}
