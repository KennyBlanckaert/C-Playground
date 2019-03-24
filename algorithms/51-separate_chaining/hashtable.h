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

                unique_ptr<Node> to_add = make_unique<Node>(word);
                current->next = move(to_add);
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
                printList(hashtable[i].get());
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

        void printList(Node* current) {
            while (current) {
                cout << current->word << " ";
                current = current->next.get();
            }
        }

        /* Fields */
        int size;
        unique_ptr<Node> hashtable[100];
};
