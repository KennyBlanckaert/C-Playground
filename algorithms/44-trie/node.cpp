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
    for (int i = 0; i < this->children.size(); i++) {
        if (this->children[i].get() != nullptr) {
            string result = this->children[i].get()->draw_recursive(out, counter, this->id);
            connections << result;
        }
    }

    return connections.str();
};