#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "graph.h"

int main(int argc, char** argv) {

    // 4 bridges - 2 articulation points
    Graph<Direction::UNDIRECTED> t_graph(5);
    t_graph.addConnection(0, 1);
    t_graph.addConnection(0, 2);
    t_graph.addConnection(0, 3);
    t_graph.addConnection(2, 4);

    // No bridges - No articulation points
    Graph<Direction::UNDIRECTED> cycle(4);
    cycle.addConnection(0, 1);
    cycle.addConnection(1, 2);
    cycle.addConnection(2, 3);
    cycle.addConnection(3, 0);

    // 2 bridges - 2 articulation points
    Graph<Direction::UNDIRECTED> graph(6);
    graph.addConnection(0, 1);
    graph.addConnection(1, 2);
    graph.addConnection(1, 5);
    graph.addConnection(3, 5);
    graph.addConnection(2, 3);
    graph.addConnection(3, 4);

    cout << "graph1: \n" << endl;
    t_graph.isDoubleConnected();
    cout << endl;
    cout << "graph2: \n" << endl;
    cycle.isDoubleConnected();
    cout << endl;
    cout << "graph3: \n" << endl;
    graph.isDoubleConnected();
    cout << endl;
    
    t_graph.draw("graph1.dot");
    cycle.draw("graph2.dot");
    graph.draw("graph3.dot");

    return 0;
}