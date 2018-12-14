void Trie::add(const string& word) {    
    Node* current = this->get();

    // Check if node contains word starting with the same letter
    bool contains = false;
    for (int i = 0; i < current->children.length(); i++) {
        string word = 
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