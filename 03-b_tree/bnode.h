#ifndef BNode_H
#define BNode_H

#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

#include "disk.h"

using namespace std;

template<class Key, class Data, unsigned int m>
class BNode {
    public:

        /* Constructors & Destructor*/
        BNode() : BNode<Key, Data, m>(true) { };                                                                 // this calls the second constructor
        BNode(bool is_leaf_node) : k(0), is_leaf_node(is_leaf_node) { /*assert(++(this->crashtest) > 10);*/ };   // this creates an empty Bnode with no children
        BNode(unsigned int l) : BNode<Key, Data, m>(false) { this->index[0] = l; };                              // this creates an empty BNode with an existing left child (used when splitted). First KEY added afterward MUST be GREATER than child !!!
        BNode(unsigned int l, const Key& sl, const Data& d, unsigned int r) : BNode<Key, Data, m>(false) {       // this creates an BNode with key, value and 2 child nodes
            this->index[0] = l;
            this->index[1] = r;
            this->key[1] = sl;
            this->data[1] = d;
            this->k++;
        };
        ~BNode() { this->crashtest--; };

        /* Copy constructor & operator */
        BNode(const BNode<Key, Data, m>& other) = default;
        BNode& operator=(const BNode<Key, Data, m>& other) = default;

        /* Move constructor & operator */
        BNode(BNode<Key, Data, m>&& other) = default;
        BNode& operator=(BNode<Key, Data, m>&& other) = default;

        /* Functions */

        // check if node contains key
        unsigned int contains(const Key& key) const {

            int i = 1;
            while (i <= this->k) {
                if (this->key[i] == key) {
                    return i;
                }
                i++;
            }

            return 0;
        };

        // check if node is a leaf
        bool is_leaf() const { return this->is_leaf_node; };

        // check if node is full
        bool is_full() const { return (this->k == m); };

        // get corresponding data from key
        Data get_value(const Key& key) const { 
            
            int position = this->contains(key);
            if (position) {
                return this->data[position];
            }
            else {
                throw "Key does not exist!";
            }
        };

        // change corresponding data from key
        void update_value(const Key& key, const Data& d) {

            int position = this->contains(key);
            if (position) {
                this->data[position] = d;
            }
            else {
                throw "Key does not exist!";
            }
        };

        // add key (with empty right child node) in sorted order
        void add(const Key& key, const Data& data) { this->add(key, data, Disk<BNode<Key, Data, m>>::NULL_BLOKINDEX); };

        // add key (with existing right child node) in sorted order
        void add(const Key& key, const Data& data, unsigned int r) {

            if (this->contains(key)) {
                throw "Key does not exist!";
            }

            if (this->is_full()) {
                throw "Node is full";
            }

            int i = this->k;
            while (i > 0 && key < this->key[i]) {
                this->key[i+1] = this->key[i];
                this->data[i+1] = this->data[i];
                this->index[i+1] = this->index[i];
                i--;
            }
            this->key[i+1] = key;
            this->data[i+1] = data;
            this->index[i+1] = r;
            
            this->k++;
            
        };

        // returns right childnode of given key
        unsigned int get_childindex(const Key& key) const {

            if (this->contains(key)) {
                throw "Key lays within this node";
            }

            int position = 1; 
            while (position <= this->k && key > this->key[position]) {
                position++;
            }
            position--;

            return this->index[position];
            
        };

        // return number of children
        unsigned int count_children() const { return (this->k + 1); };

        // set children
        void set_children(int children) { this->k = (children-1); };

        // split a full node
        void split(BNode<Key, Data, m>& brother, Key& key, Data& data) {

            // get middle
            int middle = ceil(this->k / 2);

            // set property of new node
            brother.is_leaf_node = this->is_leaf_node;

            // move keys, data and if not a leaf, the childindexes of all keys right of middle
            key = this->key[middle];
            data = this->data[middle];
            if (!this->is_leaf_node) { brother.index[0] = this->index[middle]; }

            for (int i = middle + 1; i <= k; i++) {
                brother.key[i-middle] = this->key[i];
                brother.data[i-middle] = this->data[i];
                if (!this->is_leaf_node) { brother.index[i - middle] = this->index[i]; }
            }

            // reset number of children (or set all 'deleted' keys, data and indexes to 0)
            brother.k = this->k - middle;
            this->k = middle - 1;
        };

        // get all indexes
        vector<unsigned int>& get_indexes() {
            vector<unsigned int> indexes(begin(this->index), end(this->index));
            return indexes;
        }
        
        // access Key on specific index
        Key operator[](int index) const {
            
            if (index > 0 && index <= this->k) {
                return this->key[index];
            }
            else {
                throw "Unvalid key-index";
            }
        }

    // private:

        /* Fields */
        //
        // max children in a node
        // array of keys                        (index 0 stays unused)
        // array of values                      (index 0 stays unused)
        // array of indexes to nodes on disk
        // number of children
        // is_leaf_node
        // crashtest can not be higher than 3
        const static int KEYS_IN_NODE = m + 1;
        Key key[KEYS_IN_NODE];
        Data data[KEYS_IN_NODE];
        unsigned int index[KEYS_IN_NODE];

        int k;
        bool is_leaf_node;

        static int crashtest;
};

template<class Key, class Data, unsigned int m>
int BNode<Key, Data, m>::crashtest = 0;

#endif