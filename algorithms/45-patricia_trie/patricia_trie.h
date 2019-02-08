#include "node.h"

class Patricia_Tree : unique_ptr<Node> {
   public:
        using unique_ptr<Node>::unique_ptr;

        /* Constructor & Destructor  */
        Patricia_Tree() { (*this) = make_unique<Node>(" "); };
        Patricia_Tree(unique_ptr<Node>&& patricia_tree) : unique_ptr<Node>(move(patricia_tree)) { };
        Patricia_Tree(const vector<string>& keys) {
			for (int i = 0; i < keys.size(); i++) {
				this->add(keys[i]);
			}
        };
        ~Patricia_Tree() = default;

        /* Copy constructor & operator  */
        Patricia_Tree(const Patricia_Tree& other) = default;
        Patricia_Tree& operator=(const Patricia_Tree& other) = default;

        /* Move constructor & operator */
        Patricia_Tree(Patricia_Tree &&other) = default;
        Patricia_Tree& operator=(Patricia_Tree &&other) = default;

        /* Functions */
        void add(string word);
        void generateID(unique_ptr<Node>& node);
        void draw(const char* filename);
};

#include "node.cpp"
#include "patricia_trie.cpp"
