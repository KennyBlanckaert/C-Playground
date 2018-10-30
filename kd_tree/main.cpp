#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#define COORDINATE_SYSTEM_AXES 2

#include "Point.h"
#include "KDTree.h"

using namespace std;

int main(int argc, char** argv) {

    // Open file
    // Read coordinates
    ifstream file("100points.txt");

    if (file.is_open()) {

        cout << "Building tree..." << endl;
        KDTree<COORDINATE_SYSTEM_AXES> tree;

        int x_value, y_value;
        while (file >> x_value >> y_value) { 

            int coordinates[COORDINATE_SYSTEM_AXES] = { x_value, y_value };
            Point<COORDINATE_SYSTEM_AXES> point(coordinates);
            tree.add(point);

            // cout << x_value << " " << y_value << endl;
        }
        
        cout << "Tree created" << endl << endl;

        cout << "Drawing graph..." << endl;
        tree.draw("graph.dot");
        cout << "Graph created" << endl << endl;


        int coordinates1[COORDINATE_SYSTEM_AXES] = {68, 32};                // Yes
        Point<COORDINATE_SYSTEM_AXES> p1(coordinates1);
        int coordinates2[COORDINATE_SYSTEM_AXES] = {10, 10};                // No
        Point<COORDINATE_SYSTEM_AXES> p2(coordinates2);
        int coordinates3[COORDINATE_SYSTEM_AXES] = {277, 15};               // Yes
        Point<COORDINATE_SYSTEM_AXES> p3(coordinates3);
        int coordinates4[COORDINATE_SYSTEM_AXES] = {20, 20};                // No
        Point<COORDINATE_SYSTEM_AXES> p4(coordinates4);
        int coordinates5[COORDINATE_SYSTEM_AXES] = {60, 242};               // Yes
        Point<COORDINATE_SYSTEM_AXES> p5(coordinates5);

        cout << "Point (68, 32) found? : " << (tree.search(p1) ? "Yes" : "No") << endl;
        cout << "Point (10, 10) found? : " << (tree.search(p2) ? "Yes" : "No") << endl;
        cout << "Point (277, 15) found? : " << (tree.search(p3) ? "Yes" : "No") << endl;
        cout << "Point (20, 20) found? : " << (tree.search(p4) ? "Yes" : "No") << endl;
        cout << "Point (60, 242) found? : " << (tree.search(p5)? "Yes" : "No") << endl;
        cout << endl;

        // "Nearest point algorithm" not complete!
        Point<COORDINATE_SYSTEM_AXES> closestToP1 = tree.getClosestPoint(p1);
        Point<COORDINATE_SYSTEM_AXES> closestToP3 = tree.getClosestPoint(p3);
        Point<COORDINATE_SYSTEM_AXES> closestToP5 = tree.getClosestPoint(p5);

        cout << "Closest point to (68, 32) is " << closestToP1 << endl;
        cout << "Closest point to (277, 15) is " << closestToP3 << endl;
        cout << "Closest point to (60, 242) is " << closestToP5 << endl;
    }

    file.close();

    cout << endl << "Operations completed";

    return 0;
};