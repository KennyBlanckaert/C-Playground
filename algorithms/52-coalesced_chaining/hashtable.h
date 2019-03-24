#include "node.h"

#define CELLAR 0.20
#define BASE 0.80

class HashTable {
    public:
        HashTable(int size) : size(size), base(size*BASE), cellar(size*CELLAR) { };

        int addWord(string word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            int index = hash(word);

            if (hashtable[index].get()) {
                Node* current = hashtable[index].get();
                while (current->next.get()) {
                    current = current->next.get();
                }

                int cellar_index = (size - cellar);
                cellar--;
                shared_ptr<Node> to_add = make_shared<Node>(word);
                hashtable[cellar_index] = move(to_add);

                current->next = hashtable[cellar_index];
            }
            else {
                shared_ptr<Node> to_add = make_shared<Node>(word);
                hashtable[index] = move(to_add);
            }
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
                hash %= base;
            }

            return hash;
        }

        void printNode(Node* current) {
            if (current) {
                cout << current->word;
                if (current->next.get()) cout << " -> " << current->next->word;
            }
        }

        /* Fields */
        int size;
        int base;
        int cellar;
        shared_ptr<Node> hashtable[100];
};
