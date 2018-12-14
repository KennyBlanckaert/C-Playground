class Node {
   public:

        /* Fields */
        string id;
        string text;
		bool terminator;
        vector<unique_ptr<Node>> children;

        /* Constructors & Destructor */
        Node() : character(' '), id("root"), terminator(false) { };
        Node(char character) : character(character), children(0), terminator(false), id("root") { };
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
