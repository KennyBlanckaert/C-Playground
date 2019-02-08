void Ternary_Search_Tree::add(const string& word) {    
    
    // start at root
    Ternary_Search_Tree* current = this;

    // add every character to the tree
    for (int pos = 0; pos < word.length(); pos++) {
        char character = word[pos];

        // reach an empty child
        if (current->get() == 0) {
            *current = make_unique<Node>(character);
            generateID(*current);
            current = &(current->get()->middle);
            continue;
        }   

        // follow correct way down
        char node_character = current->get()->character;
        if (node_character == ' ') {
            current->get()->character = character;
            current = &(current->get()->middle);
        }
        else if (character == node_character) {
            current = &(current->get()->middle);
        }
        else if (character < node_character) {        
            current = &(current->get()->left);
            pos--;
        }
        else {
            current = &(current->get()->right);
            pos--;
        }
    }

    // add empty node as terminator
    *current = make_unique<Node>(' ');
    current->get()->terminator = true;
    generateID(*current);
};

void Ternary_Search_Tree::generateID(unique_ptr<Node>& node) {
    stringstream ss;
    ss << node.get();  
    string id = ss.str(); 
    node.get()->setId(id);
}

void Ternary_Search_Tree::draw(const char* filename) {

    ofstream file(filename);
    int counter = 0;

    file << "digraph {\n";
    string connections = this->get()->draw_recursive(file, counter, " ");
    file << connections;
    file << "}";

    file.close();
};