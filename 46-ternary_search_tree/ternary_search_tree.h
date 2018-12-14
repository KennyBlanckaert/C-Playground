#include "node.h"

class Ternary_Search_Tree : unique_ptr<Node> {
   public:
        using unique_ptr<Node>::unique_ptr;

        /* Constructor & Destructor  */
        Ternary_Search_Tree() { (*this) = make_unique<Node>(' '); };
        Ternary_Search_Tree(unique_ptr<Node>&& ternary_search_tree) : unique_ptr<Node>(move(ternary_search_tree)) { };
        Ternary_Search_Tree(const vector<string>& keys) {
			for (int i = 0; i < keys.size(); i++) {
				this->add(keys[i]);
			}
        };
        ~Ternary_Search_Tree() = default;

        /* Copy constructor & operator  */
        Ternary_Search_Tree(const Ternary_Search_Tree& other) = default;
        Ternary_Search_Tree& operator=(const Ternary_Search_Tree& other) = default;

        /* Move constructor & operator */
        Ternary_Search_Tree(Ternary_Search_Tree &&other) = default;
        Ternary_Search_Tree& operator=(Ternary_Search_Tree &&other) = default;

        /* Functions */
        void add(const string& word);
        void draw(const char* filename);
};

#include "node.cpp"
#include "ternary_search_tree.cpp"
