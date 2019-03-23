#ifndef TREE_H
#define TREE_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

#include "node.h"

template <class Key>
class Tree : unique_ptr<Node<Key>> {
   public:
        using unique_ptr<Node<Key>>::unique_ptr;

        /* Constructor & Destructor  */
        Tree(){};
        Tree(unique_ptr<Node<Key>>&& k) : unique_ptr<Node<Key>>(move(k)) { };
        Tree(const vector<Key> &keys) {
            for (int i = 0; i < keys.size(); i++) {
                this->add(keys[i]);
            }
        };
        ~Tree() = default;

        /* Copy constructor & operator  */
        Tree(const Tree<Key> &other) = default;
        Tree &operator=(const Tree<Key> &other) = default;

        /* Move constructor & operator */
        Tree(Tree<Key> &&other) = default;
        Tree &operator=(Tree<Key> &&other) = default;

        /* Functions */
        void add(const Key &key) {

            Node<Key>* parent = nullptr;
            Tree<Key>* current = this;
            while (current->get() != nullptr) {
                parent = current->get();
                if (key < (*current).get()->key) {
                    current = &(current->get()->left);
                } 
                else {
                    current = &(current->get()->right);
                }
            }

            Tree<Key> add = make_unique<Node<Key>>(key, parent);
            (*current) = move(add);
        };

        void depth_first_search(string type) {
            Tree<Key>* current = this;
            if (type == "preorder") {
                cout << current->get()->key << " ";
                if (current->get()->left) current->get()->left.depth_first_search(type);
                if (current->get()->right) current->get()->right.depth_first_search(type);
            }
            else if (type == "inorder") {
                if (current->get()->left) current->get()->left.depth_first_search(type);
                cout << current->get()->key << " ";
                if (current->get()->right) current->get()->right.depth_first_search(type);
            }
            else if (type == "postorder") {
                if (current->get()->left) current->get()->left.depth_first_search(type);
                if (current->get()->right) current->get()->right.depth_first_search(type);
                cout << current->get()->key << " ";
            }
            else {
                cout << "Invalid search type";
            }
        }

        void draw(const char* filename) {

            ofstream out(filename);
            assert(out);

            int counter = 0;

            out << "digraph {\n";
            this->drawRecursive(out, counter);
            out << "}";
        };

        string drawRecursive(ostream& out, int& counter) {

            ostringstream content;

            if (!*this){
                content << "null" << ++counter;
                out << content.str() << " [shape=point];\n";
            }
            else {
                content << '"' << this->get()->key << '"';
                out << content.str() << "[label=\"" << this->get()->key << "\"]";
                out << ";\n";

                string left_child = this->get()->left.drawRecursive(out, counter);
                string right_child = this->get()->right.drawRecursive(out, counter);

                out << content.str() << " -> " << left_child << ";\n";
                out << content.str() << " -> " << right_child << ";\n";
            };

            return content.str();
        };
};

#endif
