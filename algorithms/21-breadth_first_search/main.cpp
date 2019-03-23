#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "graph.h"

int main(int argc, char** argv) {

    Graph<Direction::UNDIRECTED> graph(9);
    graph.addConnection(0, 1);
    graph.addConnection(1, 2);
    graph.addConnection(1, 4);
    graph.addConnection(2, 3);
    graph.addConnection(2, 4);
    graph.addConnection(2, 5);
    graph.addConnection(5, 6);
    graph.addConnection(5, 7);
    graph.addConnection(6, 8);
    graph.addConnection(7, 8);

    graph.draw("graph.dot");

    graph.breadthFirstSearch();

    return 0;
}