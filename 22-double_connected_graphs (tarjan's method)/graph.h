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

        // Graph should be connected!
        void isDoubleConnected() {
            if (!this->found) {
                depthFirstSearch();
            }
            else {
                for (int i = 0; i < this->bridges.size(); i+=2) {
                    cout << "\tBridge found between node " << this->bridges[i] << " and node " << this->bridges[i+1]  << endl;
                }
            }

            cout << endl;
            for (auto iter = this->articulation_points.begin(); iter != this->articulation_points.end(); iter++) {
                cout << "\tArticulation point found: node " << *iter  << endl;
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

            // for bridge/articulation point searching (Tarjan's algorithm)
            vector<int> low_values(nodes);
            vector<int> discovery_values(nodes);
            
            // add for-loop if start graph is not connected
            visit(startNode, -1, visited, low_values, counter);

            return visited;
        };

        void visit(int node, int parent, vector<int>& visited, vector<int>& lows, int& counter) {
            set<int> neighbors = this->connections[node];
            
            visited[node] = counter;
            lows[node] = counter;

            counter++;

            for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
                if (*iter == parent) continue;

                // first visit
                if (visited[*iter] < 0) {
                    visit(*iter, node, visited, lows, counter);
                    lows[node] = min(lows[node], lows[*iter]);

                    // bridge found
                    if (visited[node] < lows[*iter]) {
                        cout << "\tBridge found between node " << node << " and node " << *iter << endl;
                        this->found = true;
                        this->bridges.push_back(node);
                        this->bridges.push_back(*iter);

                        // check for articulation point
                        // because we found a bridge, at least one of the nodes is an articulation point
                        if (this->connections[node].size() > 1) {
                            this->articulation_points.insert(node);
                        }
                        if (this->connections[*iter].size() > 1) {
                            this->articulation_points.insert(*iter);
                        }
                    }
                }
                // already visited
                else {
                    lows[node] = min(lows[node], visited[*iter]);
                }
            }
        };
        
        // Fields
        vector<set<int>> connections;

        bool found;
        vector<int> bridges;
        set<int> articulation_points;
};
