#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define HEAP_SIZE 4

// Definitions
int getMin(vector<int>& v);

void fill_heap(queue<int>& input, vector<int>& heap);

int empty(vector<queue<int>> runs);

template<typename T>
ostream& operator << (ostream &os, queue<T> my_queue);

template<typename T>
ostream& operator << (ostream &os, vector<T> my_queue);

// Main
int main() {

    queue<int> input({ 4, 12, 29, 34, 10, 31, 20, 25, 2, 9, 13, 7, 5, 11, 45 }); 
    vector<int> heap;
    vector<int> list;
    queue<int> output;

    int run = 0;
    vector<queue<int>> runs;

    // Fill heap
    fill_heap(input, heap);

    // INTERNAL REPLACEMENT SELECTION
    while (!input.empty() && !heap.empty()) {

        // Process one run
        run++;
        while (!heap.empty()) {
            
            // Transfer minimul to output
            int min = getMin(heap);
            output.push(min);

            // Replace
            if (!input.empty()) {
                int next = input.front();
                input.pop();

                // Add to heap if greater than previous number
                if (next > min) { heap.push_back(next); }
                // Add to list if less than previous number
                else { list.push_back(next); }
            }
        }

        // Print RUN
        cout << "RUN " << run << ": " << output << "\n";
        queue<int> run;
        while (!output.empty()) {
            int number = output.front();
            output.pop();

            run.push(number);
        } 
        runs.push_back(run);  

        // Replace List to Heap     
        for (int i = 0; i < list.size(); i++) {
        	heap.push_back(list[i]);
		}
		list.clear();

        // Refresh
        fill_heap(input, heap);
    }
    cout << endl << "MERGE: ";

    // EXTERNAL MERGE SORT
    while (!empty(runs)) {
        int min;
        int position;
        bool init = false;

        // Find minimum
        for (int i = 0; i < runs.size(); i++) {
            if (!runs[i].empty()) {
                if (!init) { 
                    init = true; 
                    min = runs[i].front(); 
                    position = i;
                }
                else if (runs[i].front() < min) { 
                    min = runs[i].front(); 
                    position = i;
                } 
            }
        }

        // Print
        cout << min << " ";
        runs[position].pop();
    }

    return 0;
}

// Functions
int empty(vector<queue<int>> runs) {
    int empty = 1;
    for (int i = 0; i < runs.size(); i++) {
        if (!runs[i].empty()) { 
            empty = 0;
            break; 
        }
    }

    return empty;
}

int getMin(vector<int>& v) {
    
    int index = 0;
    int smallest = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < smallest) { smallest = v[i]; index = i;}
    }
    v.erase(v.begin() + index);
    v.shrink_to_fit();

    return smallest;
}

void fill_heap(queue<int>& input, vector<int>& heap) {
    while (!input.empty() && heap.size() < HEAP_SIZE) {
        int next = input.front();
        input.pop();

        heap.push_back(next);
    } 
}

// Operator overloading
template<typename T>
ostream& operator << (ostream &os, queue<T> my_queue) {	
    
    while(!my_queue.empty())
    {
        os << my_queue.front() << " ";
        my_queue.pop();
    }
    
    return os; 
}

template<typename T>
ostream& operator << (ostream &os, vector<T> my_vector) {	
    
    os << my_vector[0];
    for (int i = 1; i < my_vector.size(); i++) {
        os << " - " << my_vector[i];
    }
    os << endl;
    
    return os;
}