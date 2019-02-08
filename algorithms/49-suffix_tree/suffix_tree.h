#include "node.h"

class Suffix_Tree : unique_ptr<Node> {
   public:
        using unique_ptr<Node>::unique_ptr;

        /* Constructor & Destructor  */
        Suffix_Tree() { (*this) = make_unique<Node>(" "); };
        Suffix_Tree(unique_ptr<Node>&& suffix_tree) : unique_ptr<Node>(move(suffix_tree)) { };
        Suffix_Tree(const vector<string>& keys) {
			for (int i = 0; i < keys.size(); i++) {
				this->add(keys[i]);
			}
        };
        ~Suffix_Tree() = default;

        /* Copy constructor & operator  */
        Suffix_Tree(const Suffix_Tree& other) = default;
        Suffix_Tree& operator=(const Suffix_Tree& other) = default;

        /* Move constructor & operator */
        Suffix_Tree(Suffix_Tree &&other) = default;
        Suffix_Tree& operator=(Suffix_Tree &&other) = default;

        /* Functions */
        void add(string word);
        void generateID(unique_ptr<Node>& node);
        void draw(const char* filename);
};

#include "node.cpp"
#include "suffix_tree.cpp"
