template <class Key>
string Node<Key>::drawRecursive(ostream& out, int& counter, string parent) {

    // Save all connections here
    ostringstream connections;

    // Create key & connection with his parent
    out << '"' << this->key << '"' << "[label=\"" << this->key << "\"]" << ";\n";
    if (parent != "") {
        connections << '"' << parent << '"' << " -> " << '"' << this->key << '"' << ";" << endl;
    }

    // Children
    if (this->left) {
        string result = this->left.get()->drawRecursive(out, counter, to_string(this->key));
        connections << result;
    }
    else {
        counter++;
        out << "null" << to_string(counter) << " [shape=point];\n";
        connections << '"' << this->key << '"' << " -> " << "null" << to_string(counter) << ";" << endl;
    }

    if (this->right) {
        string result = this->right.get()->drawRecursive(out, counter, to_string(this->key));
        connections << result;
    }
    else {
        counter++;
        out << "null" << to_string(counter) << " [shape=point];\n";
        connections << '"' << this->key << '"' << " -> " << "null" << to_string(counter) << ";" << endl;
    }


    return connections.str();
};