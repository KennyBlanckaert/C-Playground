template <class Key>
void Tree<Key>::add(const Key& key) {

    stack<Tree*> parent_stack;

    // find place to add (top-down)
    Tree<Key>* current = this;
    while (*current && current->get()->key < key) {
        
        parent_stack.push(current);

        // left has highest priority
        if (current->get()->left) {
            current->get()->stuffed = true;
            current = &(current->get()->right);
        }
        else {
            current = &(current->get()->left);
        }       
    }

    // inserted between 2 existing nodes
    if (*current) {
        Tree<Key> add = make_unique<Node<Key>>(key);
        add.get()->left = move(*current);
        *current = move(add);
    }  
    // inserted @ leaf
    else {
        Tree<Key> add = make_unique<Node<Key>>(key);
        *current = move(add);
    }      

    cout << key << " added" << endl;

    // swap if needed (bottom-up)   
    while (!parent_stack.empty()) {
        Tree<Key>* parent = parent_stack.top();
        parent_stack.pop();

        cout << "@parent: " << parent->get()->key << endl;

        if (parent->get()->right && parent->get()->left) {
            if (parent->get()->right.get()->stuffed == true && parent->get()->left.get()->stuffed == false) {
                cout << "swapped because right child_tree was bigger" << endl;
                parent->get()->right.swap(parent->get()->left);
            }
        }
    }
};

template <class Key>
void Tree<Key>::draw(const char* filename) {

    ofstream file(filename);
    int counter = 0;

    file << "digraph {\n";
    string connections = this->get()->drawRecursive(file, counter, "");
    file << connections;
    file << "}";

    file.close();
};