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
            set<int> nodes_in_mob;

            // Create MOB
            Weighted_Graph<Direction::UNDIRECTED, int> mob(nodes);

            // keep adding connections until all nodes are in the MOB
            int from, to, weight;
            while (nodes_in_mob.size() < nodes) {
                findLowestConnectionWithoutLoop(nodes_in_mob, mob, from, to, weight);
                mob.addConnection(from, to, weight);
                nodes_in_mob.insert(from);
                nodes_in_mob.insert(to);
            }

            // if there are 2 separate components, combine them
            vector<bool> visited(nodes, false);
            mob.visiter(0, visited);
            
            if (find(visited.begin(), visited.end(), false) != visited.end()) {
                findLowestConnectionWithoutLoop(nodes_in_mob, mob, from, to, weight, true);
                mob.addConnection(from, to, weight);
                nodes_in_mob.insert(from);
                nodes_in_mob.insert(to);
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

        void findLowestConnectionWithoutLoop(set<int>& nodes_in_mob, Weighted_Graph& mob, int& from, int& to, int& weight, bool connect = false) {

            int f;
            int t;
            int lowest;
            bool init = false;

            // Iterate over all connections
            for (int i = 0; i < this->connections.size(); i++) {
                for (auto iter = this->connections[i].begin(); iter != this->connections[i].end(); iter++) {
                    
                    // IF connect is TRUE, two components must be connected to finish the MOB
                    if (!connect) { 

                        // FROM or TO node cannot not be in the MOB
                        if (find(nodes_in_mob.begin(), nodes_in_mob.end(), i) == nodes_in_mob.end() || find(nodes_in_mob.begin(), nodes_in_mob.end(), iter->first) == nodes_in_mob.end()) {
                            if (!init) {
                                f = i;
                                t = iter->first;
                                lowest = iter->second;
                                init = true;
                            }
                            else if (iter->second < lowest) {
                                f = i;
                                t = iter->first;
                                lowest = iter->second;
                            }
                        }
                    }
                    else {

                        // Find the lowest connection that is not in the MOB
                        if (mob.connections[i].find(iter->first) == mob.connections[i].end()) {
                            if (!init) {
                                f = i;
                                t = iter->first;
                                lowest = iter->second;
                                init = true;
                            }
                            else if (iter->second < lowest) {
                                f = i;
                                t = iter->first;
                                lowest = iter->second;
                            }
                        }
                    }
                }
            }

            from = f;
            to = t;
            weight = lowest;

        }

        // Functions for verification
        bool isValidNode(int number) const {
            if (number >= 0 && number < this->connections.size()) {
                return true;
            }

            return false;
        };
};
