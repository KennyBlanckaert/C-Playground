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

        // Fields
        vector<map<int, T>> connections;

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

        void kruskal() {
            int nodes = countNodes();

            // Nodes in MOB
            set<int> nodes_in_mob;

            // Create MOB
            Weighted_Graph<Direction::UNDIRECTED, int> mob(nodes);

            // Build priority queue
            priority_queue<pair<int, pair<int, int>>> sorted_connections;
            fillPriorityQueue(sorted_connections);

            // Start adding connections
            while (!sorted_connections.empty()) {
                pair<int, pair<int, int>> conn = sorted_connections.top();
                sorted_connections.pop();

                if (find(nodes_in_mob.begin(), nodes_in_mob.end(), conn.second.first) == nodes_in_mob.end() || find(nodes_in_mob.begin(), nodes_in_mob.end(), conn.second.first) == nodes_in_mob.end()) {
                    nodes_in_mob.insert(conn.second.first);
                    nodes_in_mob.insert(conn.second.second);

                    mob.addConnection(conn.second.first, conn.second.second, conn.first);
                }
            }

            // Verify connectivity
            vector<bool> visited(nodes, false);
            visiter(0, visited);

            // Connect components if needed
            bool init = false;
            int from, to, lowest_weight;
            if (find(visited.begin(), visited.end(), true) != visited.end()) {
                for (int i = 0; i < this->connections.size(); i++) {
                    for (auto iter = this->connections[i].begin(); iter != this->connections[i].end(); iter++) {
                        if (mob.connections[i].find(iter->first) == mob.connections[i].end()) {
                            if (!init) {
                                from = i;
                                to = iter->first;
                                lowest_weight = iter->second;
                                init = true;
                            }
                            else if (iter->second < lowest_weight) {
                                from = i;
                                to = iter->first;
                                lowest_weight = iter->second;
                            }
                        }
                    }
                }

                mob.addConnection(from, to, lowest_weight);
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

        void visiter(int node, vector<bool>& visited) {
            visited[node] = true;

            map<int, T> neighbors = this->connections[node];
            for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
                if (!visited[iter->first]) {
                    visiter(iter->first, visited);
                }
            }
        };

    private:
        void fillPriorityQueue(priority_queue<pair<int, pair<int, int>>>& sorted_connections) {
            for (int i = 0; i < this->connections.size(); i++) {
                for (auto iter = this->connections[i].begin(); iter != this->connections[i].end(); iter++) {
                    sorted_connections.push(make_pair(-iter->second, make_pair(i, iter->first)));
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
};
