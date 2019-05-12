#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Declarations
template<typename T>
void dual_pivot_quicksort(vector<T>& numbers, int left, int right);

template<typename T>
void partition(vector<T>& numbers, int left, int& left_pivot, int& right_pivot, int right);

ostream& operator << (ostream& os, const vector<int>& array);

// Main
int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    dual_pivot_quicksort(numbers, 0, numbers.size() - 1);
    cout << numbers;

    return 0;
}

// Definitions
template<typename T>
void dual_pivot_quicksort(vector<T>& numbers, int left, int right) {
    if (left < right) {

        // partition
        int left_pivot;
        int right_pivot;
        partition(numbers, left, left_pivot, right_pivot, right);

        // repeat for partitions
        dual_pivot_quicksort(numbers, left, left_pivot - 1);
        dual_pivot_quicksort(numbers, left_pivot + 1, right_pivot - 1);
        dual_pivot_quicksort(numbers, right_pivot + 1, right);
    }
}

template<typename T>
void partition(vector<T>& numbers, int left, int& left_pivot, int& right_pivot, int right) {

    // start condition
    // left = left_pivot, right = right_pivot
    if (numbers[left] > numbers[right]) {
        swap(numbers[left], numbers[right]);
    }

    T p = numbers[left];
    T q = numbers[right];

    int start = left + 1;
    int end = right - 1;
    int j = start;

    // Until start & end meet eachother
    while (start <= end) {

        // Determine first or last partition (middle partition numbers end there automatically)
        if (numbers[start] < p) {
            swap(numbers[start], numbers[j]);
            j++;
        }
        else if (numbers[start] >= q) {

            // Decrease end until a number is found that does not belong to the third partition
            while (numbers[end] > q && start < end) {
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

    swap(numbers[left], numbers[j]);
    swap(numbers[right], numbers[end]);

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