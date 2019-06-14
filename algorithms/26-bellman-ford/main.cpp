#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "weighted_graph.h"

int main(int argc, char** argv) {

    Weighted_Graph<Direction::UNDIRECTED, int> graph(7);
    graph.addConnection(0, 1, 2);
    graph.addConnection(0, 2, 7);
    graph.addConnection(1, 3, 1);
    graph.addConnection(2, 3, 3);
    graph.addConnection(1, 6, 2);
    graph.addConnection(2, 4, 11);
    graph.addConnection(5, 6, 5);
    graph.addConnection(4, 5, 20);

    vector<int> shortest_paths = graph.bellman_ford_algorithm(5);

    cout << "RESULT: " << endl;
    for (int i = 0; i < shortest_paths.size(); i++) {
        cout << shortest_paths[i] << " ";
    }
    cout << endl;

    graph.draw("graph.dot");

    return 0;
}