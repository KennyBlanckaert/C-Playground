void Patricia_Tree::add(string word) {    
    Node* current = this->get();

    // TODO
};

void Patricia_Tree::generateID(unique_ptr<Node>& node) {
    stringstream ss;
    ss << node.get();  
    string id = ss.str(); 
    node.get()->setId(id);
}

void Patricia_Tree::draw(const char* filename) {

    ofstream file(filename);
    int counter = 0;

    file << "digraph {\n";
    string connections = this->get()->draw_recursive(file, counter, " ");
    file << connections;
    file << "}";

    file.close();
};