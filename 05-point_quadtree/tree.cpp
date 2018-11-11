void Tree::add(const Point& point) {
            
            cout << "point to add is " << point << endl;
            if (*this) {
                cout << "root is full!" << endl;
                Tree* current = this;
                while (*current) {
                    cout << "current = " << current->get()->point << endl;
                    current = current->get()->getChildForPoint(point);
                } 

                Tree add = make_unique<Node>(point);
                *current = move(add);

                cout << "added!" << endl;
                cout << endl;
            }
            else {
                cout << "root is empty!" << endl;
                Tree add = make_unique<Node>(point);
                *this = move(add);
                cout << "added " << point << endl << endl;
            }
        }

void Tree::draw(const char* filename) {

    ofstream file(filename);
    int counter = 0;

    file << "digraph {\n";
    string connections = this->get()->drawRecursive(file, counter, "");
    file << connections;
    file << "}";

    file.close();
};