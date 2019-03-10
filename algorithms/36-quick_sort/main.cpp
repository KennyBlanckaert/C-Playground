#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Declarations
template<typename T>
void quick_sort(vector<T>& numbers, int left, int right);

ostream& operator << (ostream& os, const vector<int>& array);

// Main
int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    quick_sort(numbers, 0, numbers.size() - 1);
    cout << numbers;

    return 0;
}

// Definitions
template<typename T>
void quick_sort(vector<T>& numbers, int left, int right) {
    if (left < right) {
        int start = left;
        int end = right;
        int pos = (rand() % (right - left)) + left;
        T pivot = numbers[pos];

        while (start <= end) {

            // find number larger than the pivot in left part
            while (numbers[start] < pivot) {
                start++;
            }

            // find number smaller than the pivot in right part
            while (numbers[end] > pivot) {
                end--;
            }

            // swap numbers & continue
            if (start <= end) {
                swap(numbers[start], numbers[end]);
                start++;
                end--;
            }
        }

        // repeat for left and right part
        quick_sort(numbers, left, end);
        quick_sort(numbers, start, right);
    }
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