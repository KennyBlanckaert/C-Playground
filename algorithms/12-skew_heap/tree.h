template <class Key>
class Node;

template <class Key>
class Tree : public unique_ptr<Node<Key>> {

    public:
        using unique_ptr<Node<Key>>::unique_ptr;

        /* Constructor & Destructor  */
        Tree() { };
        Tree(vector<Key>& keys) { for (int i = 0; i < keys.size(); i++) { this->add(keys[i]); } };
        Tree(unique_ptr<Node<Key>> n) : unique_ptr<Node<Key>>(move(n)) { };
        ~Tree() = default;

        /* Copy constructor & operator  */
        Tree(const Tree<Key>& other) = default;
        Tree& operator=(const Tree<Key>& other) = default;

        /* Move constructor & operator */
        Tree(Tree<Key>&& other) = default;
        Tree& operator=(Tree<Key>&& other) = default;

        /* Functions (implementation in tree.cpp)*/
        void add(const Key& key);

        void draw(const char* filename);
};

#include "node.h"