#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include "graph.h"

int main(int argc, char** argv) {

    Graph<Direction::DIRECTED> unconncted_directed_graph(5);
    unconncted_directed_graph.addConnection(0, 1);
    unconncted_directed_graph.addConnection(0, 3);
    unconncted_directed_graph.addConnection(0, 2);
    unconncted_directed_graph.addConnection(2, 4);

    Graph<Direction::DIRECTED> connected_directed_graph(4);
    connected_directed_graph.addConnection(0, 1);
    connected_directed_graph.addConnection(1, 2);
    connected_directed_graph.addConnection(2, 3);
    connected_directed_graph.addConnection(3, 0);

    string isConnected1 = (unconncted_directed_graph.isConnected() == 0 ? "No" : "Yes");
    cout << "IsConnected first: " << isConnected1<< endl;

    string isConnected2 = (connected_directed_graph.isConnected() == 0 ? "No" : "Yes");
    cout << "IsConnected second: " << isConnected2 << endl;

    unconncted_directed_graph.draw("graph1.dot");
    connected_directed_graph.draw("graph2.dot");

    return 0;
}