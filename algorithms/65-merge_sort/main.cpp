#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Declarations
template<typename T>
void merge_sort(vector<T>& numbers, int left, int right, vector<T>& helper);

template<typename T>
void merge(vector<T>& numbers, int left, int middle, int right, vector<T>& helper);

ostream& operator << (ostream& os, const vector<int>& array);

// Main
int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    vector<int> helper(numbers.size());
    merge_sort(numbers, 0, numbers.size() - 1, helper);
    cout << numbers;

    return 0;
}

// Definitions
template<typename T>
void merge_sort(vector<T>& numbers, int left, int right, vector<T>& helper) {
    if (left != right) {
        int middle = left + floor((right - left) / 2.0);
        merge_sort(numbers, left, middle, helper);
        merge_sort(numbers, middle + 1, right, helper);
        merge(numbers, left, middle, right, helper);
    }
}

template<typename T>
void merge(vector<T>& numbers, int left, int middle, int right, vector<T>& helper) {

    int i = left;
    int j = middle + 1;
    int pos = 0;

    // reassemble
    while (i <= middle && j <= right) {
        if (numbers[i] <= numbers[j]) {
            helper[pos] = numbers[i];
            i++;
        }
        else {
            helper[pos] = numbers[j];
            j++;
        }

        pos++;
    }

    while (i <= middle) {
        helper[pos] = numbers[i];
        i++;
        pos++;
    }

    while (j <= right) {
        helper[pos] = numbers[j];
        j++;
        pos++;
    }

    // store in main array
    for (int k = left; k <= right; k++) {
        numbers[k] = helper[k - left];
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