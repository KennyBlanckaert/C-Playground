#ifndef TREE_H
#define TREE_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

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

            cout << "adding" << key << endl;
            Tree<Key> add = make_unique<Node<Key>>(key, parent);
            (*current) = move(add);

            cout << "start splay" << endl;
            splay(current);
        };

        // Rotate right if node is left child of his parent
        // Rotate left if node is right child of his parent
        // Stop if node is at the root (no parent)
        void move_to_root(Tree<Key>* node) {

            while (node->get()->parent != nullptr) {

                Tree<Key>* parent = nullptr;
                Node<Key>* p = node->get()->parent;
                if (p->parent) {
                    Node<Key>* tmp = p->parent;
                    if (tmp->left.get() && tmp->left.get()->key == p->key) {
                        parent = &(tmp->left);
                    }
                    else if (tmp->right.get() && tmp->right.get()->key == p->key) {
                        parent = &(tmp->right);
                    }
                }
                else {
                    parent = this;
                }

                cout << "parent = " << parent->get()->key << endl;

                if (parent->get()->left && parent->get()->left.get()->key == node->get()->key) {
                    cout << "rotate right" << endl;
                    parent->rotate(true);
                }
                else {
                    cout << "rotate left" << endl;
                    parent->rotate(false);
                }

                // Because the node became the parent in rotate()
                node = parent;
            }
        };

        // Note that splay & move_to_root differ:
        // The only difference is the zig-zag operation that start rotating the grandparent before the parent of the node
        // This results in a tree that decreases the original depth
        void splay(Tree<Key>* n) {

            Node<Key>* node = n->get();
            while (node->parent != nullptr) {

                Tree<Key>* parent = nullptr;
                Tree<Key>* grandparent = nullptr;
                getFamily(node, parent, grandparent);

                // perform zig
                if (grandparent == nullptr) {
                    if (node == parent->get()->left.get()) {
                        parent->rotate(true);
                    }
                    else if (node == parent->get()->right.get()) {
                        parent->rotate(false);
                    }
                }
                // perform zig-zag or zig-zag
                else {

                    // parent is left child of grandparent
                    if (*parent == grandparent->get()->left) {
                        
                        // node is left child of parent
                        if (parent->get()->left && node == parent->get()->left.get()) {
                            grandparent->rotate(true);
                            grandparent->rotate(true);          // because the parent is now rotated into grandparent
                        }
                        // node is right child of 
                        else if (parent->get()->right && node == parent->get()->right.get()) {
                            parent->rotate(false);
                            grandparent->rotate(true);
                        }
                    }
                    // parent is right child of grandparent
                    else if (*parent == grandparent->get()->right) {

                        // node is left child of parent
                        if (parent->get()->left.get() != 0 && node == parent->get()->left.get()) {
                            parent->rotate(true);
                            grandparent->rotate(false);
                        }
                        // node is right child of 
                        else if (parent->get()->right.get() != 0 && node == parent->get()->right.get()) {
                            cout << parent->get()->key << endl;
                            grandparent->rotate(false);
                            grandparent->rotate(false);         // because the parent is now rotated into grandparent
                        }
                    }
                }
            }
        };

        void rotate(bool right) {

            // Right Rotate
            if (right) {

                Tree<Key> child = move(this->get()->left);

                (*this)->left = move(child.get()->right);
                child.get()->right = move(*this);
                *this = move(child);

                

                (*this)->parent = (*this)->right->parent;
                (*this)->right->parent = this->get();
                if ((*this)->right->left) {
                    (*this)->right->left->parent = (*this)->right.get();
                }
            } 
            // Left Rotate
            else {

                Tree<Key> child = move(this->get()->right);

                (*this)->right = move(child.get()->left);
                child.get()->left = move(*this);
                *this = move(child);

                (*this)->parent = (*this)->left->parent;
                (*this)->left->parent = this->get();
                if ((*this)->left->right) {
                    (*this)->left->right->parent = (*this)->left.get();
                }     
            }
        };

        void getFamily(const Node<Key>* c, Tree<Key>*& p, Tree<Key>*& g) {
            
            Node<Key>* p_node = c->parent;

            // Zig
            // parent
            if (p_node == this->get()) {
                p = this; 
            }
            // Zig-Zig / Zig-Zag
            // parent & grandparent
            else {

                // parent
                Node<Key>* g_node = p_node->parent;
                if (p_node == g_node->left.get()) {
                    p = &(g_node->left);
                }
                else if (p_node == g_node->right.get()) {
                    p = &(g_node->right);
                }

                // grandparent
                if (g_node == this->get()) {
                    g = this; 
                }
                else {
                    Node<Key>* gg_node = g_node->parent;
                    if (g_node == gg_node->left.get()) {
                        g = &(gg_node->left);
                    }
                    else if (g_node == gg_node->right.get()) {
                        g = &(gg_node->right);
                    }
                }
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
