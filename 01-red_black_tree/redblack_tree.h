#ifndef __RBTree_H
#define __RBTree_H

#include <cstdlib>
#include <iostream>
#include <queue>
#include <memory>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>

/*
    IMPORTANT!!

    this                =>      pointer to RBTree
    *this               =>      RBTree                         =>  unique_ptr<RBNode<Key>>
    **this              =>      RBNode

    this->get()         =>      RBNode<Key>>*
    (*(this->get()))    =>      RBNode<Key>>

    dus (*this)->... spreekt velden het RBNode aan!!
*/

using namespace std;

// Enumeration color
enum RBColor {red, black};

// Node class
template <class Key>
class RBNode;

// Tree class
template <class Key>
class RBTree : public unique_ptr<RBNode<Key>>{
    public:
        using unique_ptr<RBNode<Key>>::unique_ptr;

        // Constructors
        RBTree() { };
        RBTree(unique_ptr<RBNode<Key>>&& k) : unique_ptr<RBNode<Key>>(move(k)) { };
        RBTree(const vector<Key>& keys, const vector<Key>& red_keys) { 
            for (int i = 0; i < keys.size(); i++) {
                this->add(keys[i], RBColor::black);
            }

            convertToRed(red_keys);
        };

        // Functie-declarations
        void inorder(std::function<void(const RBNode<Key>&)> visit) const {
            if (*this){
                (*this)->left.inorder(visit);
                visit(**this);
                (*this)->right.inorder(visit);
            };
        };

        bool treeOK() {
            Key* previous;
            bool valid = true;
            inorder([&previous,&valid](const RBNode<Key>& node) {
                if (previous && node.key > *previous){
                    throw "Wrong order\n";
                }
                if (node.parent && node.parent->left.get() != &node && node.parent->right.get() != &node){
                    std::ostringstream fout;
                    fout << "Invalid parent pointer " << node.key << "\n";
                    fout << "points to " << node.parent->key << "\n";
                    throw fout;
                    return;
                }
                if (!node.parent && node.color == RBColor::red) {
                    throw "Root is red";
                }
                if (node.parent && node.parent->color == RBColor::red && node.color == RBColor::red) {
                    throw "parent has red child";
                }
                return;
            });

            return valid;
        }

        void write(ostream& os) const {
            inorder([&os](const RBNode<Key>& node) {
                string k = node.color == RBColor::black ? "black" : "red";
                os<<"("<<node.key<<", "<<k<<")" ;
                os<<"\n  left child: ";
                if (node.left)
                    os<<node.left->key;
                else
                    os<<"-----";
                os<<"\n  right child: ";
                if (node.right)
                    os<<node.right->key;
                else
                    os<<"-----";
                os<<"\n";
            });
        }

        void rotate(bool left) {
            if (left) {
                RBTree<Key> child = move((*this)->right);

                (*this)->right = move(child->left);
                child.get()->left = move(*this);
                *this = move(child);

                (*this)->parent = (*this)->left->parent;
                (*this)->left->parent = this->get();
                if ((*this)->left->right) {
                    (*this)->left->right->parent = (*this)->left.get();
                }
            }
            else {
                RBTree<Key> child = move((*this)->left);

                (*this)->left = move(child->right);
                child.get()->right = move(*this);
                *this = move(child);

                (*this)->parent = (*this)->right->parent;
                (*this)->right->parent = this->get();
                if ((*this)->right->left) {
                    (*this)->right->left->parent = (*this)->right.get();
                }
            }
        }
        void add(const Key& key, RBColor color = RBColor::red) {

            RBTree<Key>* current = this;
            RBNode<Key>* parent = 0;
            while (*current && current->get()->key != key) {
                parent = current->get();
                if (key < current->get()->key) {
                    current = &(current->get()->left);
                }
                else {
                    current = &(current->get()->right);
                }
            }

            RBTree<Key> add = make_unique<RBNode<Key>>(key, color, parent);
            *current = move(add);

            this->checkColors(current);
        }

        void convertToRed(const vector<Key>& red_keys) {
            
            for (int i = 0; i < red_keys.size(); i++) {
                Key k = red_keys[i];

                RBTree<Key>* current = this;
                RBNode<Key>* parent = 0;
                while (*current && current->get()->key != k) {
                    parent = current->get();
                    if (k < current->get()->key) {
                        current = &(current->get()->left);
                    }
                    else {
                        current = &(current->get()->right);
                    }
                }

                current->get()->color = RBColor::red;
            }
        }

        void getFamily(const RBNode<Key>* c, RBTree<Key>*& p, RBTree<Key>*& g, RBTree<Key>*& u) {
            
            RBNode<Key>* p_node = c->parent;
            RBNode<Key>* g_node = p_node->parent;

            // Get grandparent tree (if exists)
            if (g_node == this->get()) {
                g = this; 
            }
            else {
                RBNode<Key>* top_node = g_node->parent;
                if (g_node == top_node->left.get()) {
                    g = &(top_node->left);
                }
                else if (g_node == top_node->right.get()) {
                    g = &(top_node->right);
                }
            }

            if (p_node == g_node->left.get()) {
                p = &(g_node->left);
                u = &(g_node->right);
            }
            else if (p_node == g_node->right.get()) {
                p = &(g_node->right);
                u = &(g_node->left);
            }
        }

        void checkColors(RBTree<Key>* current) {
            
            if ( (*current)->color == RBColor::red && (*current)->parent->color == RBColor::red ) {                

                // Nodes: current, parent, grandparent, uncle
                RBNode<Key>* c = current->get();
                RBTree<Key>* p = nullptr;
                RBTree<Key>* g = nullptr;
                RBTree<Key>* u = nullptr;

                // Get nodes
                this->getFamily(c, p, g, u);
                cout << "Current node: " << c->key << " (" << (c->color == RBColor::red ? "red" : "black") << ")" << endl;
                cout << "p node: " << p->get()->key << " (" << (p->get()->color == RBColor::red ? "red" : "black") << ")" << endl;
                cout << "g node: " << g->get()->key << " (" << (g->get()->color == RBColor::red ? "red" : "black") << ")" << endl;
                cout << "u node: " << u->get()->key << " (" << (u->get()->color == RBColor::red ? "red" : "black") << ")" << endl;

                // First scenario
                if (u->get()->color == RBColor::red) {
                    u->get()->color = RBColor::black;
                    p->get()->color = RBColor::black;

                    if (g) {
                        g->get()->color = RBColor::red;
                    }
                    else {
                        this->get()->color = RBColor::red;
                    }
                }

                // Second scenario
                else if (u->get()->color == RBColor::black) {

                    // p is linkerchild van g
                    if (g->get()->left.get()->key == p->get()->key) {
                        
                        // c is right child van p
                        if (p->get()->right && p->get()->right.get()->key == c->key) {
                            p->rotate(true);
                        }

                        p->get()->color = RBColor::black;
                        g->get()->color = RBColor::red;
                        g->rotate(false);

                    }
                    // p is right child van g
                    else if (g->get()->right.get()->key == p->get()->key) {
                        
                        // c is left child van p
                        if (p->get()->left && p->get()->left.get()->key == c->key) {
                            p->rotate(false);
                        }

                        p->get()->color = RBColor::black;
                        g->get()->color = RBColor::red;
                        g->rotate(true);

                    }
                }

                // Repeat bottom-p
                if (g != this) {    
                    this->checkColors(g);
                }
            }
        };
};

template <class Key>
class RBNode {
    friend class RBTree<Key>;

    public:

        // Constructors
        RBNode() : parent(0) { };
        RBNode(const Key& sl) : key{sl}, parent(0), color(red) { };
        RBNode(const Key& sl, RBColor k) : key(sl), parent(0), color(k) { };
        RBNode(const Key& sl, RBColor k, RBNode<Key>* o) : key(sl), parent(o), color(k) { };
        RBNode(Key&& sl) : key{move(sl)}, parent(0), color(red) { };

        // Fields
        Key key;
        RBNode<Key>* parent;
        RBTree<Key> left, right;
        RBColor color;
};

#endif
