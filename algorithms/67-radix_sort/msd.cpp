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
void radix_sort(vector<string>& numbers, int index = 0);

void radix_buckets(int bits, vector<int>& v);
void radix_buckets(vector<string>& v, int index);

template <typename T>
ostream& operator << (ostream& os, const vector<T>& array);

// Main
int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    radix_sort(numbers);
    cout << endl;

    vector<string> words = { "cat", "cow", "car", "ape", "bench", "year", "sea", "sand", "beach", "cake", "ocean", "bicycle" };
    radix_sort(words);
    cout << endl;

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
    int bits = 1;
    while (max /= 10) {		
        bits++;
    }
    bits--;

    radix_buckets(bits, v);
}

void radix_sort(vector<string>& v, int index) {		

    // Get max
    int max_length = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].length() > max_length) {
            max_length = v[i].length(); 
        }
    }
    max_length--;

    if (index < max_length) {
        radix_buckets(v, index);
    }
}

void radix_buckets(int bits, vector<int>& v) {

    vector<vector<int>> freq(10);
    for (int i = 0; i < v.size(); i++) {
        int digit = v[i] / power(10, bits) % 10;
        freq[digit].push_back(v[i]);
    }

    for (int i = 0; i < freq.size(); i++) {
        if (freq[i].size() == 1) {
            cout << freq[i][0] << " ";
        }
        else if (freq[i].size() > 1) {
            int new_bits = bits - 1;
            radix_buckets(new_bits, freq[i]);
        }
    }
}

void radix_buckets(vector<string>& v, int index) {

    vector<vector<string>> freq(26);
    for (int i = 0; i < v.size(); i++) {
        int character = v[i][index] - 'a';
        freq[character].push_back(v[i]);
    }

    for (int i = 0; i < freq.size(); i++) {
        if (freq[i].size() == 1) {
            cout << freq[i][0] << " ";
        }
        else if (freq[i].size() > 1) {
            radix_sort(freq[i], index+1);
        }
    }
}

int power(int base, int raise) {
    int result = 1;
    for (int i = 0; i < raise; i++) {
        result *= base;
    }

    return result;
}

// Operator overloading
template <typename T>
ostream& operator << (ostream& os, const vector<T>& array) {
    
    if (array.size() == 0) {
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