#ifndef TREE_H
#define TREE_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <queue>

using namespace std;

#include "node.h"

template <class Key>
class Tree : shared_ptr<Node<Key>> {
   public:
        using shared_ptr<Node<Key>>::shared_ptr;

        /* Constructor & Destructor  */
        Tree(){};
        Tree(shared_ptr<Node<Key>>&& k) : shared_ptr<Node<Key>>(move(k)) { };
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

            Tree<Key>* current = this;
            while (current->get()) {
                
                if (key < current->get()->key) {
                    if (current->get()->has_left_leaf) {
                        break;
                    }
                    else {
                        current = &(current->get()->left);
                    }
                } 
                else {
                    if (current->get()->has_right_leaf) {
                        break;
                    }
                    else {
                        current = &(current->get()->right);
                    }
                }
            }

            Tree<Key> add = make_shared<Node<Key>>(key);
            if (!(*current)) {
                (*current) = move(add);
            }
            else {
                if (key < current->get()->key) {

                    add.get()->left = current->get()->left;
                    add.get()->right = (*current);
                    current->get()->left = move(add);
                    current->get()->has_left_leaf = false;
                }
                else {

                    add.get()->left = (*current);
                    add.get()->right = current->get()->right;
                    current->get()->right = move(add);
                    current->get()->has_right_leaf = false;
                }
            }
        };

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

                if (!this->get()->has_left_leaf) {
                    string left_child = this->get()->left.drawRecursive(out, counter);
                    out << content.str() << " -> " << left_child << ";\n";
                }
                else {
                    if (this->get()->left.get()) out << '"' << this->get()->key << "\" -> \"" << this->get()->left.get()->key << "\" [style=dashed, color=grey]\n";
                }

                if (!this->get()->has_right_leaf) {
                    string right_child = this->get()->right.drawRecursive(out, counter);
                    out << content.str() << " -> " << right_child << ";\n";
                }
                else {
                    if (this->get()->right.get()) out << '"' << this->get()->key << "\" -> \"" << this->get()->right.get()->key << "\" [style=dashed, color=grey]\n";
                }
            };

            return content.str();
        };
};

#endif
