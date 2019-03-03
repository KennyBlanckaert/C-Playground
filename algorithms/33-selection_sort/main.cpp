#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <cmath>

#define LENGTH 20

using namespace std;

void selection_sort(vector<int>& numbers);
ostream& operator << (ostream& os, const vector<int>& array);

int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    selection_sort(numbers);
    cout << numbers;

    return 0;
}

void selection_sort(vector<int>& numbers) {

    for (int i = numbers.size() - 1; i >= 0; i--) {

        int max = 0;
        for (int j = 1; j <= i; j++) {
            if (numbers[j] >= numbers[max]) {
                max = j;
            }
        }

        swap(numbers[i], numbers[max]);
    }
}

ostream& operator << (ostream& os, const vector<int>& array) {
    
    os << array[0];
    for (int i = 1; i < array.size(); i++) {
        os << " - " << array[i];
    }
    os << endl;
    
    return os;
}