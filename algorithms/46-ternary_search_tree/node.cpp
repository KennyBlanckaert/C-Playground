string Node::draw_recursive(ostream& out, int& counter, string parent) {

    // save all connections here
    ostringstream connections;

    // create point
    if (this->terminator) {
        out << "\"" << this->id << "\"[label=\"" << this->character << "\" fillcolor=black style=filled fontcolor=white];\n";
    }
    else {
        out << "\"" << this->id << "\"[label=\"" << this->character << "\"];\n";
    }

    // create connection with parent
    if (parent != " ") {
        connections << "\"" << parent << "\"" << " -> " << '"' << this->id << '"' << ";" << endl;
    }

    // children
    if (this->left.get() != nullptr) {
        string result = this->left.get()->draw_recursive(out, counter, this->id);
        connections << result;
    }
    else {
        out << "null" << ++counter << " [shape=point];\n";
        connections << '"' << this->id << "\" -> \"" << "null" << counter << '"' << endl;
    }
    if (this->middle.get() != nullptr) {
        string result = this->middle.get()->draw_recursive(out, counter, this->id);
        connections << result;
    }
    else {
        out << "null" << ++counter << " [shape=point];\n";
        connections << '"' << this->id << "\" -> \"" << "null" << counter << '"' << endl;
    }
    if (this->right.get() != nullptr) {
        string result = this->right.get()->draw_recursive(out, counter, this->id);
        connections << result;
    }
    else {
        out << "null" << ++counter << " [shape=point];\n";
        connections << '"' << this->id << "\" -> \"" << "null" << counter << '"' << endl;
    }

    return connections.str();
};