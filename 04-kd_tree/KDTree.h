#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <cassert>
#include <functional>
#include <sstream>
#include <string>
#include <cmath>

#include "KDNode.h"

using namespace std;

template<unsigned int k>
class KDTree : public unique_ptr<KDNode<k>> {
    public:
        using unique_ptr<KDNode<k>>::unique_ptr;

        /* Constructor */
        KDTree() { };
        KDTree(unique_ptr<KDNode<k>>&& u) : unique_ptr<KDNode<k>>(move(u)) { };                 // Makes it possible to cast a unique_ptr<KDNode<k>> to a KDTree<k>

        /* Copy constructor & operator  */
        KDTree(const KDTree<k>& other) = default;
        KDTree& operator = (const KDTree<k>& other) = default;

        /* Move constructor & operator */
        KDTree(KDTree<k>&& other) = default;
        KDTree& operator = (KDTree<k>&& other) = default;

        /* Functions */
        void add(Point<k>& point) {
            
            if (*this) {

                unsigned int dim;
                KDTree<k>* current = this;
                KDNode<k>* parent = 0;
                while (*current) {
                    parent = current->get();
                    dim = parent->getDimension();
                    if ( point.coordinates[dim] < current->get()->point.coordinates[dim] ) {
                        current = &(current->get()->left);
                    }
                    else {
                        current = &(current->get()->right);
                    }
                }

                KDTree<k> add = make_unique<KDNode<k>>( point, ((dim+1) % k) );
                (*current) = move(add);
            }
            else {
                KDTree<k> add = make_unique<KDNode<k>>(point, 0);
                (*this) = move(add);
            }
        };

        bool search(Point<k>& point) {

            unsigned int dim = 0;
            KDTree<k>* current = this;
            KDNode<k>* parent = 0;
            while (*current && current->get()->point != point) {
                parent = current->get();
                dim = parent->getDimension();
                if ( point.coordinates[dim] < current->get()->point.coordinates[dim] ) {
                    current = &(current->get()->left);
                }
                else {
                    current = &(current->get()->right);
                }
            }

            if (*current && current->get()->point == point) {
                return true;
            }

            return false;
        };

        Point<k> getClosestPoint(Point<k>& point) {

            // Top-down to leaf (current-best)
            unsigned int dim = 0;
            KDTree<k>* current = this;
            KDNode<k>* parent = 0;
            while (*current) {
                parent = current->get();
                dim = parent->getDimension();
                if ( point.coordinates[dim] < current->get()->point.coordinates[dim] ) {
                    current = &(current->get()->left);
                }
                else {
                    current = &(current->get()->right);
                }
            }

            // Current-best found
            Point<k> shortest_point(parent->point);
            unsigned int shortest_distance = point.distanceTo(shortest_point);

            // Bottom-up
            current = this;
            while (*current) {
                if (point == shortest_point) {                                  // Unvalid condition: given point parameter could be a leaf, so that the shortest point is already set to the SAME point!
                    shortest_point = current->get()->point;
                    shortest_distance = point.distanceTo(shortest_point);
                }
                else if (point.distanceTo(current->get()->point) < shortest_distance && point != current->get()->point) {
                    shortest_point = current->get()->point;
                    shortest_distance = point.distanceTo(shortest_point);
                }

                parent = current->get();
                dim = parent->getDimension();
                if ( point.coordinates[dim] < current->get()->point.coordinates[dim] ) {
                    current = &(current->get()->left);
                }
                else {
                    current = &(current->get()->right);
                }
            }

            // Searching other part of the hypersphere by looking to points within the distance-radius

            return shortest_point;

        };

        void draw(const char* filename) {

            ofstream out(filename);
            assert(out);

            int counter = 0;

            out << "digraph {\n";
            this->drawRecursive(out, counter);
            out << "}";
        };

        string drawRecursive(ostream& out, int& counter) {

            ostringstream content;

            if (!*this){
                content << "null" << ++counter;
                out << content.str() << " [shape=point];\n";
            }
            else {
                content << '"' << this->get()->point << '"';
                out << content.str() << "[label=\"" << this->get()->point << "\"]";
                out << ";\n";

                string left_child = this->get()->left.drawRecursive(out, counter);
                string right_child = this->get()->right.drawRecursive(out, counter);

                out << content.str() << " -> " << left_child << ";\n";
                out << content.str() << " -> " << right_child << ";\n";
            };

            return content.str();
        };
};
