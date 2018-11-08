#include <stdio.h>
#include <stdlib.h>

#include "redblack_tree.h"

using namespace std;

int main() {

	// Create red-black tree
	vector<int> nodes = { 0, -4, 30, -5, -2, 15, 45, 8, 23, 37, 52, 4, 11, 19, 26, 34, 40, 48, 60, 1, 5, 9, 13, 16, 21, 24, 28, 31, 35, 39, 43, 46, 51, 54, 61 };
	vector<int> red_nodes = { 30, 8, 23, 37, 52, 1, 5, 9, 13, 16, 21, 24, 28, 31, 35, 39, 43, 46, 51, 54, 61 };
	
	RBTree<int> b(nodes, red_nodes);

	// Rotatie
	// b.roteer(true);

	// Voeg toe
	b.add(36);
	b.write(cout);
		
	return 0;
}
