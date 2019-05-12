#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <cmath>

#define LENGTH 20

using namespace std;

// Declarations
int power(int base, int power);

template<typename T>
void shell_sort(vector<T>& numbers);

void generate_tokuda_sequence(int range, vector<int>& sequence);

void generate_sedgewick_sequence(int range, vector<int>& sequence);

ostream& operator << (ostream& os, const vector<int>& array);

// Main
int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    shell_sort(numbers);
    cout << numbers;

    return 0;
}

// Definitions
template<typename T>
void shell_sort(vector<T>& numbers) {

    vector<int> sequence;

    // Sedgewick
    // generate_sedgewick_sequence(LENGTH, sequence);

    // Tokuda
    generate_tokuda_sequence(LENGTH, sequence);
    
    int index = 0;
    while (numbers.size() > sequence[index]) {
        index++;
    }
    index--;

    int step = sequence[index];
    while (step > 0) {
        for (int i = 0; i < numbers.size(); i+=step) {

            
            int j = i - step;
            T value = numbers[i];

            while (j >= 0 && value < numbers[j]) {
                numbers[j+step] = numbers[j];
                j -= step;
            }

            numbers[j+step] = value;
        }

        index--;
        step = sequence[index];
    }
}

void generate_tokuda_sequence(int range, vector<int>& sequence) {
    for (int i = 0; i < range; i++) {
        sequence.push_back(ceil(0.2 * (9 * ((double)power(9, i) / (double)power(4, i)) - 4)));
    }
}

void generate_sedgewick_sequence(int range, vector<int>& sequence) {
    for (int i = 0; i < range; i++) {
        if (i % 2 == 0) {
            sequence.push_back(9 * pow(2, i) - 9 * pow(2, i/2) + 1);
        }
        else {
            sequence.push_back(8 * pow(2, i) - 6 * pow(2, (i+1) / 2) + 1);
        }
    }
}

int power(int base, int power) {
    int result = 1;
    for (int i = 0; i < power; i++) {
        result *= base;
    }

    return result;
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