Huffman_Tree::Huffman_Tree(string filename) {
    ifstream in(filename);
    string contents((std::istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

    map<char, int> freq = build(contents);

    vector<Huffman_Tree> trees;
    for (auto iter = freq.begin(); iter != freq.end(); iter++) {
        Huffman_Tree tree = make_unique<Node>(iter->first, iter->second);
        generateID(tree);
        trees.push_back(move(tree));
    }

    while (trees.size() != 1) {
        cout << trees.size() << endl;

        // find 2 minimum
        Huffman_Tree one = move(min(trees));
        Huffman_Tree two = move(min(trees));

        // combine to one Huffman_Tree
        char character = ' ';
        int number = one.get()->n + two.get()->n;
        Huffman_Tree combined = make_unique<Node>(character, number);
        generateID(combined);
        combined.get()->left = move(one);
        combined.get()->right = move(two);

        trees.push_back(move(combined));
    }

    (*this) = move(trees[0]);
};

Huffman_Tree Huffman_Tree::min(vector<Huffman_Tree>& trees) {

    int position = 0;
    for (int i = 1; i < trees.size(); i++) {
        if (trees[i].get()->n < trees[position].get()->n) {
            position = i;
        }
    }

    Huffman_Tree min = move(trees[position]);
    trees.erase(trees.begin() + position);
    trees.shrink_to_fit();

    return min;
}

void Huffman_Tree::generateID(Huffman_Tree& tree) {
    stringstream ss;
    ss << tree.get();  
    string id = ss.str(); 
    tree.get()->setId(id);
};

map<char, int> Huffman_Tree::build(const string& text) {

    map<char, int> freq;
    for (int i = 0; i < text.length(); i++) {
        if (freq.find(text[i]) != freq.end()) {
            freq[text[i]]++;
        }
        else {
            freq.insert(make_pair(text[i], 1));
        }
    }

    return freq;
};

void Huffman_Tree::draw(const char* filename) {

    ofstream file(filename);
    int counter = 0;

    file << "digraph {\n";
    string connections = this->get()->draw_recursive(file, counter, " ");
    file << connections;
    file << "}";

    file.close();
};