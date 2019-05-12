#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>

using namespace std;

// Declarations
template<typename T>
void insertion_sort(vector<T>& numbers);

ostream& operator << (ostream& os, const vector<int>& array);

// Main
int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    insertion_sort(numbers);
    cout << numbers;

    return 0;
}

// Definitions
template<typename T>
void insertion_sort(vector<T>& numbers) {

    for (int i = 0; i < numbers.size(); i++) {
        
        int j = i - 1;
        T value = numbers[i];
        while (j >= 0 && value < numbers[j]) {
            numbers[j+1] = numbers[j];
            j--;
        }

        numbers[j+1] = value;
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