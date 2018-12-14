class Node {
   public:

        /* Fields */
        string id;
        char character;
		bool terminator;
        unique_ptr<Node> left;
        unique_ptr<Node> middle;
        unique_ptr<Node> right;

        /* Constructors & Destructor */
        Node() : character(' '), terminator(false), id("root") { };
        Node(char character) : character(character), terminator(false), id("root") { };
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

		void setTerminator(bool terminator) {
			this->terminator = terminator;
		}

        /* Functions */
        string draw_recursive(ostream& out, int& counter, string parent);
};
