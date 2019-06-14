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
        Node() : has_left_leaf(true), has_right_leaf(true) { };
        Node(const Key& k) : key(k), has_left_leaf(true), has_right_leaf(true) { };
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
        bool has_left_leaf;
        bool has_right_leaf;
};

#endif
