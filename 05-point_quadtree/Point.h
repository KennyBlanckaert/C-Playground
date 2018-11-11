class Point {
    public:

        /* Constructor */
        Point() : x(-1), y(-1) {};
        Point(int x, int y) : x(x), y(y) { };

        /* Copy constructor & operator */
        Point(const Point& other) { (*this) = other; };
        Point& operator = (const Point& other) {
            this->x = other.x;
            this->y = other.y;
        };

        /* Move constructor & operator */
        Point(Point&& other) = default;
        Point& operator = (Point&& other) = default;

        /* Functions */
        string to_string() {
            ostringstream out;
            out << "(" << this->x << ", " << this->y << ")"; ;
            return out.str();
        }

        /* Operator Overloading */
        friend ostream& operator << (ostream& out, const Point& p) {
            out << "(" << p.x << ", " << p.y << ")"; 
            return out;
        }

        bool operator == (const Point& p) const { return (this->x == p.x && this->y == p.y); }

        bool operator != (const Point& p) const { return !(this->operator==(p)); }

    // private:
        int x;
        int y;
};
