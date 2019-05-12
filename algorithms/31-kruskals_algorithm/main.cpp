#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "weighted_graph.h"

int main(int argc, char** argv) {

    Weighted_Graph<Direction::UNDIRECTED, int> graph(7);
    graph.addConnection(0, 1, 2);
    graph.addConnection(0, 2, 3);
    graph.addConnection(0, 3, 3);
    graph.addConnection(1, 2, 4);
    graph.addConnection(1, 4, 3);
    graph.addConnection(2, 3, 5);
    graph.addConnection(2, 4, 1);
    graph.addConnection(3, 5, 7);
    graph.addConnection(4, 5, 8);
    graph.addConnection(5, 6, 9);
    graph.draw("graph.dot");

    graph.kruskal();

    return 0;
}