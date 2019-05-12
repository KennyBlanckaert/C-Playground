#include <vector>
#include <set>
#include <queue>
#include <string>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <iostream>

enum Direction { DIRECTED=1, UNDIRECTED=0 }; 

template<Direction direction>
class Graph {
    public:

        // Constructor
        Graph(int nodes = 0) {
            this->connections.resize(nodes);
        };

        // Functions
        Direction getDirection() const {
            return direction;
        };

        int addNode() {
            int number_of_nodes = connections.size();
            this->connections.resize(number_of_nodes + 1);
        };          

        void addConnection(int from, int to) {
            if (!isValidNode(from) || !isValidNode(to)) {
                cout << "Unvalid nodes! \n";
            }

            if (direction == Direction::DIRECTED) {
                this->connections[from].insert(to);
            }
            else {
                this->connections[from].insert(to);
                this->connections[to].insert(from);
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

        void topological_sort() {
            int nodes = countNodes();

            Graph copy = *this;
            queue<int> zero_degrees;
            vector<int> in_degrees(nodes);
            calculateInDegree(copy, in_degrees, zero_degrees);

            while (!zero_degrees.empty()) {
                int node = zero_degrees.front();
                zero_degrees.pop();

                cout << node << " ";

                for (auto neighbor = this->connections[node].begin(); neighbor != this->connections[node].end(); neighbor++) {
                    in_degrees[*neighbor]--;
                    if (in_degrees[*neighbor] == 0) {
                        zero_degrees.push(*neighbor);
                    }
                }
            }
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
                    out << '"' << node << "\" -> \"" << *iter << "\";" << endl;
                }
            }

             out << "}";
        };

    private:

        void calculateInDegree(Graph graph, vector<int>& in_degrees, queue<int>& zero_degrees) {
            
            // Calculate in_degrees
            for (int i = 0; i < this->connections.size(); i++) {
                for (auto iter = this->connections[i].begin(); iter != this->connections[i].end(); iter++) {
                    in_degrees[*iter]++;
                }
            }

            // Store zero_degrees
            for (int i = 0; i < in_degrees.size(); i++) {
                if (in_degrees[i] == 0) {
                    zero_degrees.push(i);
                }
            }
        }

        // Functions for verification
        bool isValidNode(int number) const {
            if (number >= 0 && number < this->connections.size()) {
                return true;
            }

            return false;
        };
        
        // Fields
        std::vector<set<int>> connections;
};
