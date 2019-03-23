#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "graph.h"

int main(int argc, char** argv) {

    // No - No 
    Graph<Direction::DIRECTED> t_graph(5);
    t_graph.addConnection(0, 1);
    t_graph.addConnection(0, 2);
    t_graph.addConnection(0, 3);
    t_graph.addConnection(2, 4);

    // Yes - Yes
    Graph<Direction::UNDIRECTED> cycle(4);
    cycle.addConnection(0, 1);
    cycle.addConnection(1, 2);
    cycle.addConnection(2, 3);
    cycle.addConnection(3, 0);

    // No - No
    Graph<Direction::UNDIRECTED> graph(6);
    graph.addConnection(0, 1);
    graph.addConnection(1, 2);
    graph.addConnection(1, 5);
    graph.addConnection(3, 5);
    graph.addConnection(2, 3);
    graph.addConnection(3, 4);

    // No - Yes
    Graph<Direction::DIRECTED> special(5);
    special.addConnection(0, 2);
    special.addConnection(0, 3);
    special.addConnection(1, 0);
    special.addConnection(2, 1);
    special.addConnection(3, 2);
    special.addConnection(3, 0);
    special.addConnection(4, 3);

    cout << "graph1: \n";
    cout << "\tEulercircuit: " << (t_graph.isEulerCircuit() == 0 ? "No" : "Yes") << endl;
    cout << "\tEulerpath: " << (t_graph.isEulerPath() == 0 ? "No" : "Yes") << endl;
    cout << "graph2: \n";
    cout << "\tEulercircuit: " << (cycle.isEulerCircuit() == 0 ? "No" : "Yes") << endl;
    cout << "\tEulerpath: " << (cycle.isEulerPath() == 0 ? "No" : "Yes") << endl;
    cout << "graph3: \n";
    cout << "\tEulercircuit: " << (graph.isEulerCircuit() == 0 ? "No" : "Yes") << endl;
    cout << "\tEulerpath: " << (graph.isEulerPath() == 0 ? "No" : "Yes") << endl;
    cout << "graph4: \n";
    cout << "\tEulercircuit: " << (special.isEulerCircuit() == 0 ? "No" : "Yes") << endl;
    cout << "\tEulerpath: " << (special.isEulerPath() == 0 ? "No" : "Yes") << endl;
    
    t_graph.draw("graph1.dot");
    cycle.draw("graph2.dot");
    graph.draw("graph3.dot");
    special.draw("graph4.dot");

    return 0;
}