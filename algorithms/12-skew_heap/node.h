template <class Key>
class Node {
    friend class Tree<Key>;

    public:

        /* Constructors */
        Node() { };
        Node(const Key& key) : key(key) { };
        ~Node() = default;

        /* Copy constructor & operator */
        Node(const Node<Key>& other) = default;
        Node& operator=(const Node<Key>& other) = default;

        /* Move constructor & operator */
        Node(Node<Key>&& other) = default;
        Node& operator=(Node<Key>&& other) = default;

        /* Functions (implementation in node.cpp) */
        string drawRecursive(ostream& out, int& counter, string parent);

    private:
        Key key;
        Tree<Key> left;
        Tree<Key> right;
};

#include "node.cpp"
#include "tree.cpp"