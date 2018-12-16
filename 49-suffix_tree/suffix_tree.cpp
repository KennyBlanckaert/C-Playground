void Suffix_Tree::add(string word) {    
    Node* current = this->get();

    // a suffix-tree is actually a patricia-tree that adds all suffixes of the word in the tree
    // therefore the code of the patricia tree is still valid with an addictional for-loop iterating all suffixes
    for (int position = 0; position < word.length(); position++) {
        string suffix = word.substr(position);

        // check if node contains word starting with (at least) the same letter
        bool done = false;
        do {
            done = false;
            int failures = 0;
            for (int i = 0; i < current->children.size(); i++) {
                Node* node = current->children[i].get();
                string child_word = node->text;

                // count matching characters with the current_node text
                int index = 0;
                while (suffix[index] == child_word[index] && index < child_word.length()) {
                    index++;
                }

                // match: pop equal letters from the suffix & go to the next node
                if (index == child_word.length()) {
                    suffix = suffix.substr(index);
                    current = node;
                    break;
                }
                // match: pop equal letters & split into children (stop while-loop)
                else if (index > 0) {
                    done = true;

                    // decrease the word inside the current node
                    // create two new children containing the differences in both words
                    node->text = suffix.substr(0, index);
                    unique_ptr<Node> first_child = make_unique<Node>(child_word.substr(index));
                    unique_ptr<Node> second_child = make_unique<Node>(suffix.substr(index));
                    
                    // for drawing only
                    generateID(first_child);
                    generateID(second_child);

                    // first child inherits children from the parent
                    first_child.get()->children.swap(node->children);

                    // for drawing only
                    first_child.get()->setTerminator(node->terminator);
                    second_child.get()->setTerminator(true);

                    // parent receives the new children
                    node->children.clear();
                    node->children.shrink_to_fit();
                    node->children.push_back(move(first_child));
                    node->children.push_back(move(second_child));   

                    // for drawing only
                    node->setTerminator(false);  

                    suffix = "";
                    break;         
                }
                else { failures++; }
            }
            
            // stop loop if current node has no children (or no matching children)
            if ((current->children.size() - failures) == 0) { done = true; }
        } 
        while (!done);

        // add characters left to the current node
        if (suffix.length() != 0) {
            unique_ptr<Node> node = make_unique<Node>(suffix);
            node.get()->setTerminator(true);
            generateID(node);
            current->children.push_back(move(node));
        }
    }
};

void Suffix_Tree::generateID(unique_ptr<Node>& node) {
    stringstream ss;
    ss << node.get();  
    string id = ss.str(); 
    node.get()->setId(id);
};

void Suffix_Tree::draw(const char* filename) {

    ofstream file(filename);
    int counter = 0;

    file << "digraph {\n";
    string connections = this->get()->draw_recursive(file, counter, " ");
    file << connections;
    file << "}";

    file.close();
};