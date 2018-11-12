#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

#include "tree.h"

int main(int argc, char** argv) {

    vector<int> keys = { 40, 50, 60, 70, 80, 90, 30 };

    Tree<int> tree(keys);

    tree.draw("skew_heap.dot");

    return 0;
};