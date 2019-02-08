#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "stable_matching.h"

int main(int argc, char** argv) {

    // Initialization
    vector<string> men = { "Dries", "Kevin", "Steven", "Thibaut", "Vincent", "Eden", "Toby", "Axel", "Marouane" };
    vector<string> women = { "Annelien", "Ellen", "Julie", "Tatiane", "Virginie", "Laura", "Cilou", "Laurence", "Zeynep" };
    vector<vector<int>> men_preferences = {
        { 6, 4, 8, 1, 2, 5, 7, 3, 9 },
        { 1, 2, 3, 7, 5, 9, 4, 8, 6 },
        { 4, 6, 7, 1, 9, 5, 2, 3, 8 },
        { 4, 8, 2, 7, 9, 1, 5, 6, 3 },
        { 2, 7, 1, 9, 6, 3, 8, 4, 5 },
        { 6, 1, 7, 9, 8, 5, 3, 2, 4 },
        { 8, 5, 1, 3, 2, 7, 9, 4, 6 },
        { 9, 2, 5, 3, 4, 8, 1, 6, 7 },
        { 9, 4, 6, 2, 5, 3, 7, 8, 1 }
    };
    vector<vector<int>> women_preferences = {
        { 5, 7, 1, 6, 8, 9, 2, 4, 3 },
        { 2, 6, 8, 1, 9, 4, 3, 5, 7 },
        { 8, 1, 9, 7, 5, 2, 4, 6, 3 },
        { 3, 8, 9, 6, 4, 2, 7, 1, 5 },
        { 8, 9, 6, 5, 7, 1, 3, 4, 2 },
        { 1, 3, 7, 6, 4, 2, 8, 5, 9 },
        { 3, 8, 5, 1, 4, 6, 9, 7, 2 },
        { 6, 2, 1, 8, 4, 3, 5, 9, 7 },
        { 9, 4, 8, 5, 7, 6, 3, 2, 1 }
    };

    // Start algorithm
    Stable_Matching matching(9);
    matching.setMen(men);
    matching.setWomen(women);
    matching.setMenPreferences(men_preferences);
    matching.setWomenPreferences(women_preferences);

    // Print matches
    map<string, string> result;
    
    // Men
    result = matching.findStableMarriage(true);
    cout << endl;
    cout << "Men take initiative: " << endl;
    for (auto iter = result.begin(); iter != result.end(); iter++) {
        cout << "\t" << iter->first << " <-> " << iter->second << endl;
    }

    // Women
    result = matching.findStableMarriage(false);
    cout << endl;
    cout << "Women take initiative: " << endl;
    for (auto iter = result.begin(); iter != result.end(); iter++) {
        cout << "\t" << iter->first << " <-> " << iter->second << endl;
    }
}