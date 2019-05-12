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

        void prim() {
            int startNode = 0;
            int nodes = countNodes();
            vector<int> nodes_in_mob;
            vector<map<int, T>> neighbor_connections(nodes);

            // Create MOB
            Weighted_Graph<Direction::UNDIRECTED, int> mob(nodes);

            // Add node to MOB
            nodes_in_mob.push_back(startNode);

            // Add possible connections
            addNewNodeConnections(startNode, neighbor_connections);

            while (nodes_in_mob.size() < nodes) {
            
                // Find minimum
                int from;
                int to;
                int weight;
                findMinimumNodeConnection(nodes_in_mob, neighbor_connections, from, to, weight);

                // Add node to MOB
                nodes_in_mob.push_back(to);

                // Add connection to MOB
                mob.addConnection(from, to, weight);

                // Add the new connections
                addNewNodeConnections(to, neighbor_connections);
            }

            mob.draw("mob.dot");
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

        void addNewNodeConnections(int node, vector<map<int, T>>& neighbor_connections) {
            for (auto iter = this->connections[node].begin(); iter != this->connections[node].end(); iter++) {
                neighbor_connections[node].insert(make_pair(iter->first, iter->second));
            }
        }

        void findMinimumNodeConnection(vector<int>& nodes_in_mob, vector<map<int, T>>& neighbor_connections, int& from, int& to, int& weight) {
            
            int min;
            int f;
            int t;
            bool init = false; 
            for (int i = 0; i < neighbor_connections.size(); i++) {
                for (auto iter = neighbor_connections[i].begin(); iter != neighbor_connections[i].end(); iter++) {
                    if (find (nodes_in_mob.begin(), nodes_in_mob.end(), iter->first) != nodes_in_mob.end()) {
                        continue;
                    }
                    else if (!init) {
                        init = true;
                        f = i;
                        t = iter->first;
                        min = iter->second;
                    }
                    else if (iter->second < min) {
                        f = i;
                        t = iter->first;
                        min = iter->second;
                    }
                }
            }

            from = f;
            to = t;
            weight = min;
        }

        // Functions for verification
        bool isValidNode(int number) const {
            if (number >= 0 && number < this->connections.size()) {
                return true;
            }

            return false;
        };
        
        // Fields
        vector<map<int, T>> connections;
};
