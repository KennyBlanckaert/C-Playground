#include <vector>
#include <set>
#include <string>
#include <map>
#include <cassert>
#include <queue>
#include <fstream>
#include <algorithm>
#include <iostream>

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

        vector<int> calculate_shortest_paths_from(int node = 0) {
            int nodes = countNodes();
            vector<int> shortest_paths(nodes, 0);
            vector<bool> init(nodes, false);
            init[node] = true;
 
            bellman_ford(node, shortest_paths, init);

            return shortest_paths;
        };

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

        void bellman_ford(int node, vector<int>& solution, vector<bool>& init) {
            
            /* init is used to bypass the 0 initializations of solution */

            queue<int> to_process;
            to_process.push(node);

            // start 
            while (!to_process.empty() {

                // process first node in queue
                int startNode = to_process.front();
                to_process.pop();

                // loop all connections
                for (auto iter = this->connections[startNode].begin(); iter != this->connections[startNode].end(); iter++) {           
                    int endNode = iter->first;
                    int weight = iter->second;

                    // first time?
                    if (!init[endNode]) {
                        solution[endNode] = solution[startNode] + weight;
                        init[endNode] = true;
                        to_process.push(endNode);
                        continue;
                    }

                    // if (begin_node's score + connection's weight < end_node's score) => change score
                    if (solution[startNode] + weight < solution[endNode]) {
                        solution[endNode] = solution[startNode] + weight;
                        to_process.push(endNode);
                    }
                }
            }
        };

        void visit() {

        };
        
        // Fields
        vector<map<int, T>> connections;
};
