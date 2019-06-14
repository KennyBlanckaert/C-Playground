#include <vector>
#include <set>
#include <string>
#include <map>
#include <cassert>
#include <queue>
#include <fstream>
#include <algorithm>
#include <iostream>

#define INFINITY 1000000

enum Direction { DIRECTED=1, UNDIRECTED=0 }; 

template<Direction direction, class T>
class Weighted_Graph {
    public:

        // Constructor
        Weighted_Graph(int nodes = 0) : connections(nodes) { };

        // Functions
        Direction getDirection() const {
            return direction;
        };

        int addNode() {
            int number_of_nodes = connections.size();
            this->connections.resize(number_of_nodes + 1);
        };          

        void addConnection(int from, int to, T weight) {
            if (!isValidNode(from) || !isValidNode(to)) {
                cout << "Unvalid nodes! \n";
            }

            if (direction == Direction::DIRECTED) {
                this->connections[from].insert(make_pair(to, weight));
            }
            else {
                this->connections[from].insert(make_pair(to, weight));
                this->connections[to].insert(make_pair(from, weight));
            }
        }; 

        void deleteConnection(int from, int to) {
            if (!isValidNode(from) || !isValidNode(to)) {
                throw "Unvalid nodes!";
            }

            if (direction == Direction::DIRECTED) {
                this->connections[from].erase(to);
            }
            else {
                this->connections[from].erase(to);
                this->connections[to].erase(from);
            }
        };

        int countNodes() const {
            return this->connections.size();
        };

        int countConnections() const {
            int connections = 0;
            for (int i = 0; i < this->connections.size(); i++) {
                connections += this->connections[i].size();
            }

            return connections;
        };

        vector<vector<int>> floyd_algorithm(int node = 0) {

            int nodes = countNodes();
            vector<vector<int>> matrix(nodes);

            buildMatrix(matrix);

            floyd(matrix);

            return matrix;
        }

        void draw(string filename) const {
            ofstream out(filename);
            assert(out);

            out << "digraph {\n";

            int nodes = countNodes();
            while (--nodes != -1) {
                out << '"' << nodes << "\"[label=\"" << nodes << "\"];" << endl;
            }

            for (int node = 0; node < countNodes(); node++) {

                for (auto iter = this->connections[node].begin(); iter != this->connections[node].end(); iter++) {
                    out << '"' << node << "\" -> \"" << iter->first << "\";" << endl;
                }
            }

             out << "}";
        };

    private:

        // Functions for verification
        bool isValidNode(int number) const {
            if (number >= 0 && number < this->connections.size()) {
                return true;
            }

            return false;
        };

        void buildMatrix(vector<vector<int>>& matrix) {
            
            int size = matrix.size();
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i].resize(size, INFINITY);
                matrix[i][i] = 0;

                for (auto iter = this->connections[i].begin(); iter != this->connections[i].end(); iter++) {
                    int endNode = iter->first;
                    int weight = iter->second;
                    
                    matrix[i][endNode] = weight;
                }
            }
        }

        void floyd(vector<vector<int>>& matrix) {
            
            int nodes = countNodes();
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[i].size(); j++) {
                    if (matrix[i][j] == INFINITY) {

                        for (int k = 0; k < nodes; k++) {
                            if (matrix[k][j] != 0 && matrix[i][k] != 0 && matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                                matrix[i][j] = matrix[i][k] + matrix[k][j];
                            }
                        }
                    }
                }
            }
        }

        // Fields
        vector<map<int, T>> connections;
};
