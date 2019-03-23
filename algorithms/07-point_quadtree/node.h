#define CHILDREN 4

class Node {
    public:

        /* Constructors */
        Node() { };
        Node(Point p) : point(p) { };
        ~Node() = default;

        /* Copy constructor & operator */
        Node(const Node& other) = default;
        Node& operator=(const Node& other) = default;

        /* Move constructor & operator */
        Node(Node&& other) = default;
        Node& operator=(Node&& other) = default;

        /* Functions (implementation in node.cpp) */
        Point& getPoint();

        Tree* getChildForPoint(const Point& point);

        string drawRecursive(ostream& out, int& counter, string parent);

    // private:
        Point point;
        Tree children[CHILDREN];
};

#include "node.cpp"
#include "tree.cpp"