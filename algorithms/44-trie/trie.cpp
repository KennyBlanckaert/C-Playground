void Trie::add(const string& word) {    
    Node* current = this->get();
    for (int i = 0; i < word.length(); i++) {
        char character = word[i];

        bool contains = false;
        for (int j = 0; j < current->children.size(); j++) {
            Node* child = current->children[j].get();

            if (child->character == character) {
                contains = true;
                current = child;                
            }            
        }

        if (!contains) {
            unique_ptr<Node> node = make_unique<Node>(character);

            // id is used to distinct nodes with the same character (to draw graph)
            // terminator is used to determine the ending of a word
            stringstream ss;
            ss << node.get();  
            string id = ss.str(); 
            node.get()->setId(id);
            if (i == word.size() - 1) { node.get()->setTerminator(true); }

            current->children.push_back(move(node));
            current = current->children[current->children.size() - 1].get();
        }
    }
};

void Trie::draw(const char* filename) {

    ofstream file(filename);
    int counter = 0;

    file << "digraph {\n";
    string connections = this->get()->draw_recursive(file, counter, " ");
    file << connections;
    file << "}";

    file.close();
};