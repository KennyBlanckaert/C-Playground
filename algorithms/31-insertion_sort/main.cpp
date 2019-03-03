#include <stdlib.h>
#include <stdio.h>

#include <vector>
#include <iostream>

using namespace std;

void insertion_sort(vector<int>& numbers);
ostream& operator << (ostream& os, const vector<int>& array);

int main(int argc, char** argv) {

    vector<int> numbers = { 10, 11, 9, 7, 20, 100, 37, 84, 61, 3, 92, 52, 35, 27, 17, 42, 62, 69, 89, 90, 12 };
    insertion_sort(numbers);
    cout << numbers;

    return 0;
}

void insertion_sort(vector<int>& numbers) {

    for (int i = 0; i < numbers.size(); i++) {
        
        int j = i - 1;
        int number = numbers[i];
        while (j >= 0 && number < numbers[j]) {
            numbers[j+1] = numbers[j];
            j--;
        }

        numbers[j+1] = number;
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