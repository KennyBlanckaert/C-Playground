#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "graph.h"

int main(int argc, char** argv) {

    Graph<Direction::DIRECTED> graph(6);
    graph.addConnection(0, 1);
    graph.addConnection(0, 2);
    graph.addConnection(0, 3);
    graph.addConnection(0, 4);
    graph.addConnection(2, 1);
    graph.addConnection(2, 5);
    graph.addConnection(4, 3);
    graph.addConnection(5, 3);

    graph.draw("graph.dot");

    graph.topological_sort();

    return 0;
}