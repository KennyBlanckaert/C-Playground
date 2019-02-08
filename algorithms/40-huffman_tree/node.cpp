string Node::draw_recursive(ostream& out, int& counter, string parent) {

    // save all connections here
    ostringstream connections;

    // create point
    out << "\"" << this->id << "\"[label=\"" << this->character << " (" << this->n << ")" << "\"];\n";

    // create connection with parent
    if (parent != " ") {
        connections << "\"" << parent << "\"" << " -> " << '"' << this->id << '"' << ";" << endl;
    }

    // children
    if (this->left.get() != nullptr) {
        string result = this->left.get()->draw_recursive(out, counter, this->id);
        connections << result;
    }
    if (this->right.get() != nullptr) {
        string result = this->right.get()->draw_recursive(out, counter, this->id);
        connections << result;
    }

    return connections.str();
};