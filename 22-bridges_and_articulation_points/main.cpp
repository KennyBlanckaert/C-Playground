#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "graph.h"

int main(int argc, char** argv) {

    // 4 bridges
    Graph<Direction::DIRECTED> t_graph(5);
    t_graph.addConnection(0, 1);
    t_graph.addConnection(0, 3);
    t_graph.addConnection(0, 2);
    t_graph.addConnection(2, 4);

    // No bridges
    Graph<Direction::DIRECTED> cycle(4);
    cycle.addConnection(0, 1);
    cycle.addConnection(1, 2);
    cycle.addConnection(2, 3);
    cycle.addConnection(3, 0);

    // 2 bridges
    Graph<Direction::DIRECTED> graph(4);
    graph.addConnection(0, 1);
    graph.addConnection(1, 2);
    graph.addConnection(1, 5);
    graph.addConnection(3, 5);
    graph.addConnection(2, 3);
    graph.addConnection(3, 4);

    // t_graph.findBridges();
    // cycle.findBridges();
    // graph.findBridges();

    t_graph.draw("graph1.dot");
    cycle.draw("graph2.dot");
    // graph.draw("graph3.dot");

    return 0;
}