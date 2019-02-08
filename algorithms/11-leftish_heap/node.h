template <class Key>
class Node {
    friend class Tree<Key>;

    public:

        /* Constructors */
        Node() : stuffed(false) { };
        Node(const Key& key) : key(key), stuffed(false) { };
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
        bool stuffed;
        Tree<Key> left;
        Tree<Key> right;
};

#include "node.cpp"
#include "tree.cpp"