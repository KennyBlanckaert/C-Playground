#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <type_traits>

using namespace std;

// Declarations
int power(int base, int raise);

void radix_sort(vector<int>& numbers);
void radix_sort(vector<string>& numbers);

void insertion_sort(vector<int>& v, int base);
void insertion_sort(vector<string>& v, int index);

template <typename T>
ostream& operator << (ostream& os, const vector<T>& array);

// Main
int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    radix_sort(numbers);
    cout << numbers;

    vector<string> words = { "cat", "cow", "car", "ape", "bench", "year", "sea", "sand", "beach", "cake", "ocean", "bicycle" };
    radix_sort(words);
    cout << words;

    return 0;
}

// Definitions
void radix_sort(vector<int>& v) {		
    
    // Get max
    int max = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > max) {
            max = v[i]; 
        }
    }
    
    // Get radix from int
    int radix = 1;
    while (max /= 10) {		
        radix++;
    }
    
    // Sort
    for (int i = 0; i < radix; i++) {
        
        // Insertion sort
        int base = power(10, i);
        insertion_sort(v, base);
    }
}

void radix_sort(vector<string>& v) {		

    // Get max
    int radix = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].length() > radix) {
            radix = v[i].length(); 
        }
    }
    radix--;
    
    // Sort
    for (int i = radix; i >= 0; i--) {   
        
        // Insertion sort
        insertion_sort(v, i);
    }
}

int power(int base, int raise) {
    int result = 1;
    for (int i = 0; i < raise; i++) {
        result *= base;
    }

    return result;
}

void insertion_sort(vector<int>& v, int base) {
    for (int j = 0; j < v.size(); j++) {
                 			
        int current = v[j];
        int character = v[j] / base % 10;

        int k = j - 1;     
        while (k >= 0 && character < (v[k] / base % 10) ) {
            v[k+1] = v[k];
            k--;
        }
        v[k+1] = current;
    }
}

void insertion_sort(vector<string>& v, int index) {
    for (int j = 0; j < v.size(); j++) {
                 			
        string current = v[j];
        char character = v[j][index];

        int k = j - 1;     
        while (k >= 0 && character < v[k][index] ) {
            v[k+1] = v[k];
            k--;
        }
        
        v[k+1] = current;
    }
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