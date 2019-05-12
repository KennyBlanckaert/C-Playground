#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>

using namespace std;

// Declarations
template<typename T>
void heap_sort(vector<T>& numbers);

template<typename T>
void heapify(vector<T>& numbers, int parent, int size);

ostream& operator << (ostream& os, const vector<int>& array);

// Main
int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    heap_sort(numbers);
    cout << numbers;

    return 0;
}

// Definitions
template<typename T>
void heap_sort(vector<T>& numbers) {

    // change to max-heap array
    int heap_size = numbers.size();
    for (int parent = numbers.size() / 2; parent >= 0; parent--) {
        heapify(numbers, parent, heap_size);
    }

    // swap max-element with last position
    // decrease heap-size
    swap(numbers[0], numbers[heap_size - 1]);
    heap_size--;

    // repeat until heap equals zero
    while (heap_size > 0) {
        heapify(numbers, 0, heap_size);

        swap(numbers[0], numbers[heap_size - 1]);
        heap_size--;
    }
}

template<typename T>
void heapify(vector<T>& numbers, int parent, int size) {

    int root = parent;
    int left_child = parent * 2 + 1;
    int right_child = parent * 2 + 2;

    if (left_child < size && numbers[left_child] > numbers[root]) {
        root = left_child;
    }

    if (right_child < size && numbers[right_child] > numbers[root]) {
        root = right_child;
    }

    if (root != parent) {
        swap(numbers[root], numbers[parent]);
        heapify(numbers, root, size);
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