Point& Node::getPoint() {
    return this->point;
};

Tree* Node::getChildForPoint(const Point& point) {
    
    // Upper-left
    if (point.x <= this->point.x && point.y > this->point.y) {
        return &(children[0]);
    }
    // Upper-right
    else if (point.x > this->point.x && point.y > this->point.y) {
        return &(children[1]);
    }
    // Lower-left
    else if (point.x <= this->point.x && point.y <= this->point.y) {
        return &(children[2]);
    }
    // Lower-right
    else if (point.x > this->point.x && point.y <= this->point.y) {
        return &(children[3]);
    }
};

string Node::drawRecursive(ostream& out, int& counter, string parent) {

    // Save all connections here
    ostringstream connections;

    // Create point & connection with his parent
    out << '"' << this->point << '"' << "[label=\"" << this->point << "\"]" << ";\n";
    if (parent != "") {
        connections << '"' << parent << '"' << " -> " << '"' << this->point << '"' << ";" << endl;
    }

    // Children
    for (int i = 0; i < 4; i++) {
        if (this->children[i]) {
            string result = this->children[i].get()->drawRecursive(out, counter, this->point.to_string());
            connections << result;
        }
        else {
            counter++;
            out << "null" << to_string(counter) << " [shape=point];\n";
            connections << '"' << this->point << '"' << " -> " << "null" << to_string(counter) << ";" << endl;
        }
    }


    return connections.str();
};