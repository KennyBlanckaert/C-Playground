#ifndef __RZWTree_H
#define __RZWTree_H

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
    BELANGRIJK!!

    this                =>      pointer naar een RZWTree
    *this               =>      RZWTree                         =>  unique_ptr<RZWNode<Key>>
    **this              =>      RZWNode

    this->get()         =>      RZWNode<Key>>*
    (*(this->get()))    =>      RZWNode<Key>>

    dus (*this)->... spreekt velden het RZWNode aan!!
*/

using namespace std;

// Enumeration color
enum RZWColor {red, black};

// Node class
template <class Key>
class RZWNode;

// Tree class
template <class Key>
class RZWTree : public unique_ptr<RZWNode<Key>>{
    public:
        using unique_ptr<RZWNode<Key>>::unique_ptr;

        // Constructors
        RZWTree() { };
        RZWTree(unique_ptr<RZWNode<Key>>&& k) : unique_ptr<RZWNode<Key>>(move(k)) { };
        RZWTree(const vector<Key>& keys, const vector<Key>& red_keys) { 
            for (int i = 0; i < keys.size(); i++) {
                this->add(keys[i], RZWColor::black);
            }

            convertToRed(red_keys);
        };

        // Functie-declaraties
        void inorder(std::function<void(const RZWNode<Key>&)> visit) const {
            if (*this){
                (*this)->left.inorder(visit);
                visit(**this);
                (*this)->right.inorder(visit);
            };
        };

        bool treeOK() {
            Key* previous;
            bool valid = true;
            inorder([&previous,&valid](const RZWNode<Key>& node) {
                if (previous && node.key > *previous){
                    throw "Verkeerde volgorde\n";
                }
                if (node.parent && node.parent->left.get() != &node && node.parent->right.get() != &node){
                    std::ostringstream fout;
                    fout << "Ongeldige parentpointer bij node " << node.key << "\n";
                    fout << "wijst naar " << node.parent->key << "\n";
                    throw fout;
                    return;
                }
                if (!node.parent && node.color == RZWColor::red) {
                    throw "Rode wortel";
                }
                if (node.parent && node.parent->color == RZWColor::red && node.color == RZWColor::red) {
                    throw "parent heeft red child";
                }
                return;
            });

            return valid;
        }

        void write(ostream& os) const {
            inorder([&os](const RZWNode<Key>& node) {
                string k = node.color == RZWColor::black ? "black" : "red";
                os<<"("<<node.key<<", "<<k<<")" ;
                os<<"\n  Linkerchild: ";
                if (node.left)
                    os<<node.left->key;
                else
                    os<<"-----";
                os<<"\n  Rechterchild: ";
                if (node.right)
                    os<<node.right->key;
                else
                    os<<"-----";
                os<<"\n";
            });
        }

        void rotate(bool left) {
            if (left) {
                RZWTree<Key> child = move((*this)->right);

                // Pointer verleggen
                (*this)->right = move(child->left);
                child.get()->left = move(*this);
                *this = move(child);

                // parents wijzigen
                (*this)->parent = (*this)->left->parent;
                (*this)->left->parent = this->get();
                if ((*this)->left->right) {
                    (*this)->left->right->parent = (*this)->left.get();
                }
            }
            else {
                RZWTree<Key> child = move((*this)->left);

                // Pointer verleggen
                (*this)->left = move(child->right);
                child.get()->right = move(*this);
                *this = move(child);

                // parents wijzigen
                (*this)->parent = (*this)->right->parent;
                (*this)->right->parent = this->get();
                if ((*this)->right->left) {
                    (*this)->right->left->parent = (*this)->right.get();
                }
            }
        }
        void add(const Key& key, RZWColor color = RZWColor::red) {

            RZWTree<Key>* current = this;
            RZWNode<Key>* parent = 0;
            while (*current && current->get()->key != key) {
                parent = current->get();
                if (key < current->get()->key) {
                    current = &(current->get()->left);
                }
                else {
                    current = &(current->get()->right);
                }
            }

            RZWTree<Key> add = make_unique<RZWNode<Key>>(key, color, parent);
            *current = move(add);

            this->checkColors(current);
        }

        void convertToRed(const vector<Key>& red_keys) {
            
            for (int i = 0; i < red_keys.size(); i++) {
                Key k = red_keys[i];

                RZWTree<Key>* current = this;
                RZWNode<Key>* parent = 0;
                while (*current && current->get()->key != k) {
                    parent = current->get();
                    if (k < current->get()->key) {
                        current = &(current->get()->left);
                    }
                    else {
                        current = &(current->get()->right);
                    }
                }

                current->get()->color = RZWColor::red;
            }
        }

        void getFamily(const RZWNode<Key>* c, RZWTree<Key>*& p, RZWTree<Key>*& g, RZWTree<Key>*& u) {
            
            RZWNode<Key>* p_node = c->parent;
            RZWNode<Key>* g_node = p_node->parent;

            // Get grandparent tree (if exists)
            if (g_node == this->get()) {
                g = this; 
            }
            else {
                RZWNode<Key>* top_node = g_node->parent;
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

        void checkColors(RZWTree<Key>* current) {
            
            if ( (*current)->color == RZWColor::red && (*current)->parent->color == RZWColor::red ) {                

                // Nodes: current, parent, grandparent, uncle
                RZWNode<Key>* c = current->get();
                RZWTree<Key>* p = nullptr;
                RZWTree<Key>* g = nullptr;
                RZWTree<Key>* u = nullptr;

                // Get nodes
                this->getFamily(c, p, g, u);
                cout << "Current node: " << c->key << " (" << (c->color == RZWColor::red ? "red" : "black") << ")" << endl;
                cout << "p node: " << p->get()->key << " (" << (p->get()->color == RZWColor::red ? "red" : "black") << ")" << endl;
                cout << "g node: " << g->get()->key << " (" << (g->get()->color == RZWColor::red ? "red" : "black") << ")" << endl;
                cout << "u node: " << u->get()->key << " (" << (u->get()->color == RZWColor::red ? "red" : "black") << ")" << endl;

                // First scenario
                if (u->get()->color == RZWColor::red) {
                    u->get()->color = RZWColor::black;
                    p->get()->color = RZWColor::black;

                    if (g) {
                        g->get()->color = RZWColor::red;
                    }
                    else {
                        this->get()->color = RZWColor::red;
                    }
                }

                // Second scenario
                else if (u->get()->color == RZWColor::black) {

                    // p is linkerchild van g
                    if (g->get()->left.get()->key == p->get()->key) {
                        
                        // c is rechterchild van p
                        if (p->get()->right && p->get()->right.get()->key == c->key) {
                            p->rotate(true);
                        }

                        p->get()->color = RZWColor::black;
                        g->get()->color = RZWColor::red;
                        g->rotate(false);

                    }
                    // p is rechterchild van g
                    else if (g->get()->right.get()->key == p->get()->key) {
                        
                        // c is linkerchild van p
                        if (p->get()->left && p->get()->left.get()->key == c->key) {
                            p->rotate(false);
                        }

                        p->get()->color = RZWColor::black;
                        g->get()->color = RZWColor::red;
                        g->rotate(true);

                    }
                }

                // Bottom-Up werken
                if (g != this) {    
                    this->checkColors(g);
                }
            }
        };
};

template <class Key>
class RZWNode {
    friend class RZWTree<Key>;

    public:

        // Constructors
        RZWNode() : parent(0) { };
        RZWNode(const Key& sl) : key{sl}, parent(0), color(red) { };
        RZWNode(const Key& sl, RZWColor k) : key(sl), parent(0), color(k) { };
        RZWNode(const Key& sl, RZWColor k, RZWNode<Key>* o) : key(sl), parent(o), color(k) { };
        RZWNode(Key&& sl) : key{move(sl)}, parent(0), color(red) { };

        // Fields
        Key key;
        RZWNode<Key>* parent;
        RZWTree<Key> left, right;
        RZWColor color;
};

#endif
