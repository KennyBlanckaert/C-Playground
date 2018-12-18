string Node::draw_recursive(ostream& out, int& counter, char parent) {

    // save all connections here
    ostringstream connections;

    // create point
    out << "\"" << this->character << "\"[label=\"" << this->character << "\"];\n";

    // create connection with parent
    if (parent != ' ') {
        connections << "\"" << parent << "\"" << " -> " << '"' << this->character << '"' << ";" << endl;
    }

    // children
    if (this->left.get() != nullptr) {
        string result = this->left.get()->draw_recursive(out, counter,this->character);
        connections << result;
    }
    if (this->right.get() != nullptr) {
        string result = this->right.get()->draw_recursive(out, counter, this->character);
        connections << result;
    }

    return connections.str();
};