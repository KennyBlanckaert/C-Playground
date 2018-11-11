#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <cassert>
#include <string>
#include <sstream>

using namespace std;

#include "point.h"
#include "tree.h"

int main(int argc, char** argv) {

    fstream file("100points.txt");

    Tree tree;
    if (file.is_open()) {

        int x_value, y_value;
        while (file >> x_value >> y_value) {
            Point point(x_value, y_value);
            tree.add(point);
        }
    }

    tree.draw("tree.dot");

    return 0;
}