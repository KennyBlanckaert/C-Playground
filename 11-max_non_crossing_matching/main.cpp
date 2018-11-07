#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main() {

	// Open file
    ifstream file{"bridges.dat"};

	// Read amount of malls
    int lines;
    file >> lines;

	// Vectors
    vector<int> prices;
    vector<int> malls;
    vector<int> partial_solutions;
    vector<int> precursors;

    // Read lines
    for (int i = 0; i < lines; i++) {
    	
        int g, l;
        
        file >> g;
        file >> l;
        
        prices.push_back(g);
        malls.push_back(l);
        partial_solutions.push_back(g);
        precursors.push_back(-1); 			// -1 = currenly no precursor
    }

    // iterate over all bridges
    for (int i = 0; i < lines; i++) {
    	
        // iterate over all bridges left of i
        for (int j = 0; j < i; j++) {
        	
            // do not cross
            if (malls[j] < malls[i]) {
				
				// IF bridge before does not exist or new possibility is better
                if (precursors[i] == -1 || partial_solutions[j] > partial_solutions[precursors[i]]) {
                    precursors[i] = j;
                    partial_solutions[i] = partial_solutions[j] + prices[i];
                }
            }
        }
    }

    // highest profit
    int best = 0;
    
    for (int i = 0; i < lines; i++) {
        
		if (partial_solutions[i] > partial_solutions[best]) {
            best = i;
        }
    }
    
    cout << "profit = " << partial_solutions[best] << " euries" << endl << endl;

    // solution
    cout << "bridges : " << endl << endl << best << endl;
    
    int previous = precursors[best];
    while (previous != -1) {
        cout << previous << endl;
        previous = precursors[previous];
    }

    return 0;
}
