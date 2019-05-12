#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Declarations
template<typename T>
void duplicate_pivot_quicksort(vector<T>& numbers, int left, int right);

template<typename T>
void partition(vector<T>& numbers, int left, int& left_pivot, int& right_pivot, int right);

ostream& operator << (ostream& os, const vector<int>& array);

// Main
int main(int argc, char** argv) {

    vector<int> numbers = { 1, 5, 6, 2, 3, 1, 3, 2, 5, 2, 1, 4, 2, 3, 2, 5, 2, 3, 4, 7 };
    duplicate_pivot_quicksort(numbers, 0, numbers.size() - 1);
    cout << numbers;

    return 0;
}

// Definitions
template<typename T>
void duplicate_pivot_quicksort(vector<T>& numbers, int left, int right) {
    if (left < right) {

        // partition
        int left_pivot;
        int right_pivot;
        partition(numbers, left, left_pivot, right_pivot, right);

        // repeat for partitions (middle partition are duplicates = already in place)
        duplicate_pivot_quicksort(numbers, left, left_pivot);
        duplicate_pivot_quicksort(numbers, right_pivot, right);
    }
}

template<typename T>
void partition(vector<T>& numbers, int left, int& left_pivot, int& right_pivot, int right) {

    int pos = (rand() % (right - left)) + left;
    T p = numbers[pos];
    swap(numbers[pos], numbers[right]);

    int start = left;
    int end = right;
    int j = start;

    cout << "pivot: " << p << endl;
    cout << numbers;

    // Until start & end meet eachother
    while (start <= end) {

        // Determine first or last partition (middle partition numbers end there automatically)
        if (numbers[start] < p) {
            swap(numbers[start], numbers[j]);
            j++;
        }
        else if (numbers[start] > p) {

            // Decrease end until a number is found that does not belong to the third partition
            while (numbers[end] > p && start < end) {
                end--;
            }

            swap(numbers[start], numbers[end]);
            end--;

            // Verify the new number at start 
            if (numbers[start] < p) {
                swap(numbers[start], numbers[j]);
                j++;
            }
        }

        // Next number
        start++;
    }
    j--;
    end++;

    cout << numbers;
    cout << "left pivot: " << j << endl;
    cout << "right pivot: " << end << endl << endl;
    

    left_pivot = j;
    right_pivot = end;
}

// Operator overloading
ostream& operator << (ostream& os, const vector<int>& array) {
    
    os << array[0];
    for (int i = 1; i < array.size(); i++) {
        os << " - " << array[i];
    }
    os << endl;
    
    return os;
}