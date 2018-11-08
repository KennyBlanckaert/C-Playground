#ifndef BTREE_H
#define BTREE_H

#include <stack>
#include <string>
#include <sstream>
#include <unordered_set>
#include <queue>
#include <vector>

#include "disk.h"
#include "bnode.h"

#define MAX_OCCURRENCES_AMOUNT 10

using namespace std;

template<class Key, class Data, unsigned int m>
class BTree {

    public:

        /* Constructor & Destructor  */
        BTree(Disk<BNode<Key, Data, m>>& disk) : disk(disk) { this->root = BNode<Key, Data, m>(true); this->rootindex = disk.write(this->root); };
        ~BTree() = default;

        /* Copy constructor & operator  */
        BTree(const BTree<Key, Data, m>& other) = default;
        BTree& operator=(const BTree<Key, Data, m>& other) = default;

        /* Move constructor & operator */
        BTree(BTree<Key, Data, m>&& other) = default;
        BTree& operator=(BTree<Key, Data, m>&& other) = default;

        /* Functions */
        Data search(const Key& key) const {

            BNode<Key, Data, m> current_node = this->root;
            unsigned int current_index = this->rootindex;

            // top-down-ascend
            while (!current_node.is_leaf()) {
                if (current_node.contains(key)) {
                    return current_node.get_value(key);
                }

                current_index = current_node.get_childindex(key);
                current_node = this->disk.read(current_index);
            }

            if (current_node.contains(key)) {
                return current_node.get_value(key);
            }
            else {
                return 0;
            }
        };

        void add(const Key& key, const Data& data) {
            
            // Store max occurences
            this->save(key, data);

            // Save or Change data
            BNode<Key, Data, m> current_node = this->root;
            unsigned int current_index = this->rootindex;

            stack<unsigned int> parent_stack;

            while (!current_node.is_leaf()) {

                parent_stack.push(current_index);
                if (current_node.contains(key)) {
                    
                    current_node.update_value(key, data);
                    if (current_index == this->rootindex) {
                        this->root = current_node;
                    }

                    disk.overwrite(current_index, current_node);
                    return;
                }

                current_index = current_node.get_childindex(key);
                current_node = this->disk.read(current_index);
            }

            // leaf node
            if (current_node.contains(key)) {
                       
                current_node.update_value(key, data);
                if (current_index == this->rootindex) {
                    this->root = current_node;
                }

                disk.overwrite(current_index, current_node);
                return;
            }

            // IMPROVEMENT: only split when adding to a full node!
            current_node.add(key, data);

            // Start splitting (up to the root if needed)
            while (current_node.is_full() && current_index != this->rootindex && !parent_stack.empty()) {
                Key key_to_move_up;
                Data value_to_move_up;
                BNode<Key, Data, m> new_brother;
                current_node.split(new_brother, key_to_move_up, value_to_move_up);

                disk.overwrite(current_index, current_node);
                unsigned int new_brother_index = disk.write(new_brother);

                current_index = parent_stack.top();
                parent_stack.pop();
                current_node = disk.read(current_index);

                current_node.add(key_to_move_up, value_to_move_up, new_brother_index);
            }

            // Are we at the root?
            if (current_index == this->rootindex) {
                this->root = current_node;
            }

            // Root is not full
            if (!this->root.is_full()) {
                disk.overwrite(current_index, current_node);
            } 
            // Root is full
            else {
                Key key_to_move_up;
                Data value_to_move_up;
                BNode<Key, Data, m> new_brother;
                this->root.split(new_brother, key_to_move_up, value_to_move_up);                    /*              this->root                  */
                                                                                                    /*                /    \                    */
                disk.overwrite(this->rootindex, this->root);                                        /*               /      \                   */  
                unsigned int new_brother_index = disk.write(new_brother);                           /*              /        \                  */
                                                                                                    /*     old_rootindex  new_brother_index     */          
                // create new root node & add to disk                                                                                 
                this->root = BNode<Key, Data, m>(this->rootindex, key_to_move_up, value_to_move_up, new_brother_index);
                this->rootindex = disk.write(this->root);
            }
        };

        void save(const Key& key, const Data& data) {

            // Add?
            if (data > this->min) {

                // Already in set?
                bool contains = false;
                int key_position = 0;

                int min_position = 0;

                for (int i = 0; i < this->max_occurrences.size(); i++) {
                    if (key == this->max_occurrences[i].first) {
                        contains = true;
                        key_position = i;
                    }
                    
                    if (this->max_occurrences[i].second < this->min) {
                        this->min = this->max_occurrences[i].second;
                        min_position = i;
                    }
                }

                if (contains) {
                    this->max_occurrences[key_position].second = data;
                }
                else {
                    if (this->max_occurrences.size() == MAX_OCCURRENCES_AMOUNT) {
                        this->max_occurrences.erase(this->max_occurrences.begin() + min_position);
                        this->max_occurrences.shrink_to_fit();
                    }

                    this->max_occurrences.push_back(make_pair(key, data));
                    this->min = this->max_occurrences[0].second;
                }
            }
        };

        vector<pair<Key, Data>>& getHighestOccurrences() {
            return this->max_occurrences;
        }

    private:

        /* Fields */
        //
        // Disk where nodes are stored
        // The root node
        // The root index on the disk
        Disk<BNode<Key, Data, m>>& disk;
        BNode<Key, Data, m> root;
        unsigned int rootindex;

        // To get highest occurences
        static Data min;
        vector<pair<Key, Data>> max_occurrences;                    /* A set can not be used, because set-data can NOT be modified!!! (IMPROVEMENT: iterator) */
};

template<class Key, class Data, unsigned int m>
Data BTree<Key, Data, m>::min = 0;

#endif