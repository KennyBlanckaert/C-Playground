#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "weighted_graph.h"

int main(int argc, char** argv) {

    Weighted_Graph<Direction::UNDIRECTED, int> graph(5);
    graph.addConnection(0, 1, 3);
    graph.addConnection(0, 4, 1);
    graph.addConnection(1, 2, 6);
    graph.addConnection(1, 3, 8);
    graph.addConnection(2, 3, 2);

    vector<vector<int>> floyd_matrix = graph.floyd_algorithm(5);

    cout << "RESULT: " << endl;
    for (int i = 0; i < floyd_matrix.size(); i++) {
        for (int j = 0; j < floyd_matrix[i].size(); j++) {
            cout << floyd_matrix[i][j] << "\t";
        }
        cout << endl;
    }

    graph.draw("graph.dot");

    return 0;
}