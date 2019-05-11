#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

// Declarations
template<typename T>
int quick_sort(vector<T>& v, int left, int right);

ostream& operator << (ostream& os, const vector<int>& array);

// Main
int main(int argc, char** argv) {
    srand(time(NULL));

    vector<int> v = { 1, 5, 6, 2, 3, 1, 3, 2, 5, 2, 1, 4, 2, 3, 2, 5, 2, 3, 4, 7 };
    quick_sort(v, 0, v.size() - 1);
    cout << v;

    return 0;
}

// Definitions
template<typename T>
int quick_sort(vector<T>& v, int left, int right) {		 
    if (left < right) {

        // choose random pivot & swap it with last value
        int pos = (rand() % (right - left)) + left;
        T pivot = v[pos];
        swap(v[pos], v[right]);

        // partion according to pivot
        int i = left - 1;
        int dups = 0;
        if (left < right) {
            for (int j = left; j < right; j++) {
                if (v[j] < pivot) {
                    i++;
                    swap(v[i], v[j]);
                }
                // remove duplicates to combine afterwards
                else if (v[j] == pivot) {
                    v.erase(v.begin() + j);
                    dups++;
                    right--;
                    j--;
                }
            }
        
            i++;
            swap(v[i], v[right]);

            // group all pivot duplicates in the middle
            for (int k = 0; k < dups; k++) { v.insert(v.begin()+i, pivot); right++; }

            // repeat for left and right part
            quick_sort(v, left, i - 1);
            quick_sort(v, i + dups + 1, right);
        }
    }
}

// Operator overloading
ostream& operator << (ostream& os, const vector<int>& array) {
    
    if (array.size() == 0)  {
        os << endl;
        return os;
    }

    os << array[0];
    for (int i = 1; i < array.size(); i++) {
        os << " - " << array[i];
    }
    os << endl;
    
    return os;
}