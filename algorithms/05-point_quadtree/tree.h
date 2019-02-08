class Node;

class Tree : public unique_ptr<Node> {

    public:
        using unique_ptr<Node>::unique_ptr;

        /* Constructor & Destructor  */
        Tree() { };
        Tree(unique_ptr<Node> n) : unique_ptr<Node>(move(n)) { };
        ~Tree() = default;

        /* Copy constructor & operator  */
        Tree(const Tree& other) = default;
        Tree& operator=(const Tree& other) = default;

        /* Move constructor & operator */
        Tree(Tree&& other) = default;
        Tree& operator=(Tree&& other) = default;

        /* Functions (implementation in tree.cpp)*/
        void add(const Point& point);

        void draw(const char* filename);
};

#include "node.h"