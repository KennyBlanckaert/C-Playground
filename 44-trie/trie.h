#include "node.h"

class Trie : unique_ptr<Node> {
   public:
        using unique_ptr<Node>::unique_ptr;

        /* Constructor & Destructor  */
        Trie() { (*this) = make_unique<Node>('*'); };
        Trie(unique_ptr<Node>&& trie) : unique_ptr<Node>(move(trie)) { };
        Trie(const vector<string>& keys) {
			for (int i = 0; i < keys.size(); i++) {
				this->add(keys[i]);
			}
        };
        ~Trie() = default;

        /* Copy constructor & operator  */
        Trie(const Trie& other) = default;
        Trie& operator=(const Trie& other) = default;

        /* Move constructor & operator */
        Trie(Trie &&other) = default;
        Trie& operator=(Trie &&other) = default;

        /* Functions */
        void add(const string& word);
        void draw(const char* filename);
};

#include "node.cpp"
#include "trie.cpp"
