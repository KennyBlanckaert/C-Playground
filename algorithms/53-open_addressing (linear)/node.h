class Node {
   public:

        /* Fields */
        string word;
        shared_ptr<Node> next;

        /* Constructors & Destructor */
        Node() { };
        Node(string word) : word(word) { };
        ~Node() = default;

        /* Copy constructor & operator */
        Node(const Node& other) = default;
        Node& operator=(const Node& other) = default;

        /* Move constructor & operator */
        Node(Node&& other) = default;
        Node& operator=(Node&& other) = default;
};
