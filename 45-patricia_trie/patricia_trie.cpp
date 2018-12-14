void Patricia_Tree::add(string word) {    
    Node* current = this->get();

    // Check if node contains word starting with the same letter
    bool done = false;
    int word_length_left = word.length();
    do {
        done = false;
        int failures = 0;
        for (int i = 0; i < current->children.size(); i++) {
            Node* node = current->children[i].get();
            string child_word = node->text;

            int index = 0;
            int equal_characters = 0;
            while (word[index] == child_word[index] && equal_characters < child_word.length()) {
                equal_characters++;
                index++;
            }

            cout << "equal character: " << equal_characters << endl;

            // match: pop equal letters from word & go to the next node
            word_length_left -= equal_characters;
            if (equal_characters == child_word.length()) {
                cout << "equal: going deeper" << endl;
                word = word.substr(equal_characters);
                current = node;
                break;
            }
            // match: pop equal letters & split into children (stop while-loop)
            else if (equal_characters > 0) {
                cout << "partly equal: splitting" << endl;
                done = true;
                word_length_left = 0;

                node->text = word.substr(0, equal_characters);
                unique_ptr<Node> first_child = make_unique<Node>(child_word.substr(equal_characters));
                unique_ptr<Node> second_child = make_unique<Node>(word.substr(equal_characters));
                generateID(first_child);
                generateID(second_child);

                first_child.get()->children.swap(node->children);
                first_child.get()->setTerminator(node->terminator);
                second_child.get()->setTerminator(true);
                node->children.clear();
                node->children.shrink_to_fit();
                node->children.push_back(move(first_child));
                node->children.push_back(move(second_child));   
                node->setTerminator(false);  

                break;         
            }
            else { failures++; }
        }
        
        // stop loop if current node has no children (or no matching children)
        if ((current->children.size() - failures) == 0) { done = true; }
    } 
    while (!done);

    cout << "loop done" << endl;

    // add characters left to the current node
    if (word_length_left != 0) {
        cout << "add node: " << word << endl;
        unique_ptr<Node> node = make_unique<Node>(word);
        node.get()->setTerminator(true);
        generateID(node);
        current->children.push_back(move(node));
    }
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