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

        void depthFirstSearch(int startNode = 0) {     
            
            int nodes = countNodes();
            if (isValidNode(startNode)) {

                vector<bool> visited(nodes, false);
                visiter(startNode, visited);
            }
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

        void visiter(int node, vector<bool>& visited) {
            visited[node] = true;
            cout << node << " ";

            set<int> neighbors = this->connections[node];
            for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
                if (!visited[*iter]) {
                    visiter(*iter, visited);
                }
            }
        };
        
        // Fields
        std::vector<set<int>> connections;
};
