#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "graph.h"

int main(int argc, char** argv) {

    Graph<Direction::UNDIRECTED> undirected_graph(7);
    undirected_graph.addConnection(0, 1);
    undirected_graph.addConnection(1, 2);
    undirected_graph.addConnection(3, 4);
    undirected_graph.addConnection(4, 5);
    undirected_graph.addConnection(5, 6);

    Graph<Direction::DIRECTED> directed_graph(7);
    directed_graph.addConnection(0, 1);
    directed_graph.addConnection(0, 2);
    directed_graph.addConnection(1, 3);
    directed_graph.addConnection(3, 2);
    directed_graph.addConnection(2, 4);
    directed_graph.addConnection(1, 6);
    directed_graph.addConnection(5, 6);
    directed_graph.addConnection(5, 4);

    undirected_graph.draw("graph1.dot");
    directed_graph.draw("graph2.dot");

    undirected_graph.transitive_closure("transitive_closure1.dot");
    directed_graph.transitive_closure("transitive_closure2.dot");

    return 0;
}