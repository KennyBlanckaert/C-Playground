#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <type_traits>
#include <algorithm>
#include <ctime>

using namespace std;

// Declarations
template<typename T>
T select_operator(vector<T>& v, int k);

template<typename T>
int quick_sort_step(vector<T>& v, int left, int right);

template <typename T>
ostream& operator << (ostream& os, const vector<T>& array);

// Main
int main(int argc, char** argv) {
    srand(time(NULL));

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };

    // Index 8 should be the value 20
    // Index 12 should be the value 42
    // Index 18 should be the value 89
    int k_value = select_operator(numbers, 8);
    cout << "The k-th smallest value = " << k_value << endl;

}

// Definitions
template<typename T>
T select_operator(vector<T>& v, int k) {
    int search = k - 1;
    int left = 0;
    int right = v.size() - 1;

    while (left < right) {

        // partition table with pivot_pos in the middle
        int pivot_pos = quick_sort_step(v, left, right);
        
        // continue with left part
        if (search < pivot_pos) {
            right = pivot_pos - 1;
        }
        // continue with right part
        else if (search > pivot_pos) {
            left = pivot_pos + 1;
        }
        // already found!
        else {
            return v[pivot_pos];
        }
    }

    return v[k - 1];
}

/* MUST GUARANTEE PERFECT PARTIIONING (previous quicksort version isn't always perfectly partioned) */
template<typename T>
int quick_sort_step(vector<T>& v, int left, int right) {		

    // choose random pivot & swap it with last value
    int pos = (rand() % (right - left)) + left;
    T pivot = v[pos];
    swap(v[pos], v[right]);

    // partion according to pivot
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (v[j] <= pivot) {
            i++;
            swap(v[i], v[j]);
        }
    }

    i++;
    swap(v[i], v[right]);

    return i;
}

// Operator overloading
template <typename T>
ostream& operator << (ostream& os, const vector<T>& array) {
    
    os << array[0];
    for (int i = 1; i < array.size(); i++) {
        os << " - " << array[i];
    }
    os << endl;
    
    return os;
}