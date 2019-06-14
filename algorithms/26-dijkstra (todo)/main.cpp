#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "weighted_graph.h"

int main(int argc, char** argv) {

    Weighted_Graph<Direction::UNDIRECTED, int> graph(2);
    graph.addConnection(0, 1, 2);
    graph.draw("graph.dot");

    // graph.dijkstra();

    return 0;
}