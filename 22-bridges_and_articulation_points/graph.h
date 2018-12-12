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

            this->bridgesFound = false;
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

            this->bridgesFound = false;
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
        void findBridges() {
            if (this->bridgesFound) {
                depthFirstSearch();
            }
            else {
                for (int i = 0; i < this->bridges.size(); i+=2) {
                    cout << "Bridge found between node " << this->bridges[i] << " and node " << this->bridges[i+1]  << endl;
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

            // For bridge searching
            vector<int> low_values(nodes);
            vector<int> discovery_values(nodes);
            
            visit(startNode, visited, counter);

            return visited;
        };

        void visit(int node, vector<int>& visited, vector<int>& lows, vector<int>& discs, int& counter) {
            set<int> neighbors = this->connections[node];
            
            visited[node] = counter;
            lows[node] = counter;
            discs[node] = counter;

            counter++;

            for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
                if (visited[*iter] < 0) {
                    visit(*iter, visited, counter);
                    lows[node] = min(lows[node], lows[*iter]);

                    // bridge found
                    if (discs[node] < lows[*iter]) {
                        cout << "Bridge found between node " << node << " and node " << *iter << endl;
                        this->bridgesFound = true;
                        this->bridges.push_back(node);
                        this->bridges.push_back(*iter);
                    }
                }
                else {
                    lows[node] = min(lows[node], discs[*iter]);
                }
            }
        };
        
        // Fields
        vector<set<int>> connections;

        bool bridgesFound;
        vector<int> bridges;
};
