class Node {
   public:

        /* Fields */
        int n;
        char character;
		string id;
        Huffman_Tree left;
        Huffman_Tree right;

        /* Constructors & Destructor */
        Node() : character(' '), n(0) { };
        Node(char character, int number) : character(character), n(number) { };
        ~Node() = default;

        /* Copy constructor & operator */
        Node(const Node& other) = default;
        Node& operator=(const Node& other) = default;

        /* Move constructor & operator */
        Node(Node&& other) = default;
        Node& operator=(Node&& other) = default;

        /* Setters */
        void setId(string id) {
			this->id = id;
        }

        /* Functions */
        string draw_recursive(ostream& out, int& counter, string parent);
};
