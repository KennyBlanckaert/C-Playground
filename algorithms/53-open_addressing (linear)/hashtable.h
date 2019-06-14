#include "node.h"

class HashTable {
    public:
        HashTable(int size) : size(size) { };

        int addWord(string word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            int index = hash(word);

            if (hashtable[index].get()) {
                Node* current = hashtable[index].get();
                while (current->next.get()) {
                    current = current->next.get();
                }

                int start = index;
                index++;
                while (hashtable[index].get() && index != start) {
                    index++;
                    index %= size;
                }

                if (index == start) { cout << "Hashtable is full!" << endl; return -1; }

                unique_ptr<Node> to_add = make_unique<Node>(word);
                hashtable[index] = move(to_add);

                current->next = move(hashtable[index]);
            }
            else {
                unique_ptr<Node> to_add = make_unique<Node>(word);
                hashtable[index] = move(to_add);
            }

            return index;
        };

        void print() {
            for (int i = 0; i < size; i++) {
                cout << (i+1) << ": ";
                printNode(hashtable[i].get());
                cout << endl;
            }
        }

    private:

        int hash(string word) {
            int hash = 0;
            for (int i = 0; i <= word.length(); i++) {
                hash *= 10;
                hash += (word[i] - 'a');
                hash %= size;
            }

            return hash;
        }

        void printNode(Node* current) {
            if (current) {
                cout << current->word;
                while (current->next.get()) {
                    cout << " -> " << current->next->word;
                    current = current->next.get();
                }
            }
        }

        /* Fields */
        int size;
        unique_ptr<Node> hashtable[100];
};
