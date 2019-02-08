#include <stdio.h>
#include <stdlib.h>

#include "redblack_tree.h"

using namespace std;

int main() {

	// all nodes & red nodes
	vector<int> nodes = { 0, -4, 30, -5, -2, 15, 45, 8, 23, 37, 52, 4, 11, 19, 26, 34, 40, 48, 60, 1, 5, 9, 13, 16, 21, 24, 28, 31, 35, 39, 43, 46, 51, 54, 61 };
	vector<int> red_nodes = { 30, 8, 23, 37, 52, 1, 5, 9, 13, 16, 21, 24, 28, 31, 35, 39, 43, 46, 51, 54, 61 };
	
	// create RBTree
	RBTree<int> red_black_tree(nodes, red_nodes);

	// use graphviz to create an image of the tree
	red_black_tree.draw("red_black_tree_start.dot");

	// add red node
	// verify if the parent is red and if so, use red-black tree scenarios to fix it
	red_black_tree.add(36);

	// use graphviz to create an image of the tree
	red_black_tree.draw("red_black_tree_after_add.dot");
		
		return 0;
}
