#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "tree.h"

using namespace std;


/* 
    Creating the splay_tree                 WORKS
    Rotate                                  WORKS
    Splaying after every add/search           X             
*/
int main() {
    
    vector<int> keys = {50, 40, 30, 45, 35, 55, 60, 51};
    Tree<int> splay_tree(keys);

    splay_tree.draw("tree.dot");

    return 0;
}
