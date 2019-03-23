#ifndef Node_H
#define Node_H

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace std;

template <class Key>
class Tree;

template <class Key>
class Node {
   public:

        /* Constructors & Destructor*/
        Node() : parent(0) { };
        Node(const Key& k) : key(k), parent(0) { };
        Node(const Key& k, Node<Key>* p) : key(k), parent(p) { };
        ~Node() = default;

        /* Copy constructor & operator */
        Node(const Node<Key>& other) = default;
        Node& operator=(const Node<Key>& other) = default;

        /* Move constructor & operator */
        Node(Node<Key>&& other) = default;
        Node& operator=(Node<Key>&& other) = default;

        /* Functions */

        /* Fields */
        Key key;
        Tree<Key> left;
        Tree<Key> right;
        Node<Key>* parent;
};

#endif
