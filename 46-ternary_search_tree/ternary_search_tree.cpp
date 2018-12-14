void Ternary_Search_Tree::add(const string& word) {    
    Node* current = this->get();
    
};

void Ternary_Search_Tree::draw(const char* filename) {

    ofstream file(filename);
    int counter = 0;

    file << "digraph {\n";
    string connections = this->get()->draw_recursive(file, counter, " ");
    file << connections;
    file << "}";

    file.close();
};