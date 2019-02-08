#include <stdlib.h>
#include <stdio.h>

using namespace std;

template <unsigned int k>
class KDTree;

template <unsigned int k>
class KDNode {
    public:
        friend class KDTree<k>;

        /* Constructors */
        KDNode(Point<k>& p, unsigned int d) : point(p), depth(d) { };

        /* Functions */
        unsigned int getDimension() {
            return this->depth % k;
        }

    private:
        KDTree<k> left;
        KDTree<k> right;
        Point<k> point;
        unsigned int depth;

};