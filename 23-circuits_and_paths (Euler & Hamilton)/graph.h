#include <vector>
#include <set>
#include <string>
#include <cassert>
#include <fstream>
#include <algorithm>

enum Direction { DIRECTED=1, UNDIRECTED=0 }; 

template<Direction direction>
class Graph {
    public:

        // Constructor
        Graph(int nodes = 0) : found(false), bridges(0) {
            this->connections.resize(nodes);

        };

        // Functions
        Direction getDirection() const {
            return direction;
        };

        int addNode() {
            int number_of_nodes = connections.size();
            this->connections.resize(number_of_nodes + 1);

            this->found = false;
            this->bridges.clear();
            this->bridges.shrink_to_fit();
        };          

        void addConnection(int from, int to) {
            if (!isValidNode(from) || !isValidNode(to)) {
                cout << "Unvalid nodes!\n";
                return;
            }

            if (direction == Direction::DIRECTED) {
                this->connections[from].insert(to);
            }
            else {
                this->connections[from].insert(to);
                this->connections[to].insert(from);
            }

            this->found = false;
            this->bridges.clear();
            this->bridges.shrink_to_fit();
        }; 

        void deleteConnection(int from, int to) {
            if (!isValidNode(from) || !isValidNode(to)) {
                cout << "Unvalid nodes!\n";
                return;
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

        bool isEulerCircuit() {
            // UNDIRECTED
            // All degrees must be even
            if (direction == Direction::UNDIRECTED) {
                for (int i = 0; i < countNodes(); i++) {
                    if (this->connections[i].size() % 2 != 0) { return false; }
                }

                return true;
            }
            // DIRECTED
            // for every node: in-degree = out-degree
            else {
                int nodes = countNodes();
                vector<int> ins(nodes);
                vector<int> outs(nodes);

                // count ins & outs
                for (int i = 0; i < nodes; i++) {
                    outs[i] += this->connections[i].size();
                    for (auto iter = this->connections[i].begin(); iter != this->connections[i].end(); iter++) {
                        ins[*iter]++;
                    }
                }

                // verify
                for (int i = 0; i < nodes; i++) {
                    if (ins[i] != outs[i]) { return false; }
                }

                return true;
            }
        }

        bool isEulerPath() {
            // UNDIRECTED
            // Up to 2 nodes may have an odd degree
            if (direction == Direction::UNDIRECTED) {
                int odds = 0;
                for (int i = 0; i < countNodes(); i++) {
                    if (this->connections[i].size() % 2 != 0) { odds++; }
                }

                return (odds <= 2 ? true : false);
            }
            // DIRECTED
            // one node has: in-degree = out-degree + 1
            // one node has: in-degree + 1 = out-degree
            // all other nodes have: in-degree = out-degree
            else {
                int nodes = countNodes();
                vector<int> ins(nodes);
                vector<int> outs(nodes);

                // count ins & outs
                for (int i = 0; i < nodes; i++) {
                    outs[i] += this->connections[i].size();
                    for (auto iter = this->connections[i].begin(); iter != this->connections[i].end(); iter++) {
                        ins[*iter]++;
                    }
                }

                // verify
                vector<bool> diffs(2, false);
                for (int i = 0; i < nodes; i++) {
                    if (ins[i] == outs[i]) { continue; }
                    else {
                        if (ins[i] + 1 == outs[i]) { 
                            if (!diffs[0]) {
                                diffs[0] = true;
                            }
                            else {
                                return false;
                            }
                        }         
                        else if (ins[i] == outs[i] + 1) {
                            if (!diffs[1]) {
                                diffs[1] = true;
                            }
                            else {
                                return false;
                            }
                        }
                        else {
                            return false;
                        }
                    }
                }

                return (diffs[0] && diffs[1]);
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

        // Functions for verification
        bool isValidNode(int number) const {
            if (number >= 0 && number < this->connections.size()) {
                return true;
            }

            return false;
        };

        vector<int> depthFirstSearch(int startNode = 0) {
            int counter = 0;
            int nodes = countNodes();
            vector<int> visited(nodes, -1);
            
            // add for-loop if start graph is not connected
            visit(startNode, -1, visited, counter);

            return visited;
        };

        void visit(int node, int parent, vector<int>& visited, int& counter) {
            set<int> neighbors = this->connections[node];
            
            visited[node] = counter;
            counter++;

            for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
                if (*iter == parent) continue;

                // first visit
                if (visited[*iter] < 0) {
                    visit(*iter, node, visited, counter);
                }
            }
        };
        
        // Fields
        vector<set<int>> connections;

        bool found;
        vector<int> bridges;
        set<int> articulation_points;
};
