class Node;

class Huffman_Tree : public unique_ptr<Node> {
   public:
        using unique_ptr<Node>::unique_ptr;

        /* Constructor & Destructor  */
        Huffman_Tree(string filename);
        Huffman_Tree(unique_ptr<Node>&& Huffman_Tree) : unique_ptr<Node>(move(Huffman_Tree)) { };
        ~Huffman_Tree() = default;

        /* Copy constructor & operator  */
        Huffman_Tree(const Huffman_Tree& other) = default;
        Huffman_Tree& operator=(const Huffman_Tree& other) = default;

        /* Move constructor & operator */
        Huffman_Tree(Huffman_Tree &&other) = default;
        Huffman_Tree& operator=(Huffman_Tree &&other) = default;

        /* Functions */
        map<char, int> build(const string& text);
        void draw(const char* filename);
		Huffman_Tree min(vector<Huffman_Tree>& trees);
};

#include "node.h"

#include "node.cpp"
#include "huffman.cpp"
