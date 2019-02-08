#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void buildLCS(vector<vector<int>>& table, vector<vector<char>>& characters, int i, int j, vector<string>& results, int& index);

int main(int argc, char** argv) {

	string word_n = "aloysius";
	string word_m = "louis";

	int n = word_n.length();
	int m = word_m.length();

	// initialize tables
	vector<vector<char>> chars(m);
	vector<vector<int>> table(m+1);
	for (int i = 0; i < chars.size(); i++) {
		chars[i].resize(n);
	}
	for (int i = 0; i < table.size(); i++) {
		
		table[i].resize(n+1);
		table[i][0] = 0;
		for (int j = 0; j < table[i].size(); j++) {
			table[0][j] = 0;
		}
	}

	// build tables
	for (int i = 1; i < table.size(); i++) {	
		for (int j = 1; j < table[i].size(); j++) {

			int up = table[i-1][j];
			int left = table[i][j-1];
			int up_left = table[i-1][j-1];
			if (word_m[i-1] == word_n[j-1]) {
				table[i][j] = up_left + 1;
				chars[i-1][j-1] = word_m[i-1];
			}
			else {
				int maximum = max(up, left);
				table[i][j] = maximum;
				chars[i-1][j-1] = '+';
			}
		}
	}

	// print tables
	for (int i = 0; i < table.size(); i++) {	
		for (int j = 0; j < table[i].size(); j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < chars.size(); i++) {	
		for (int j = 0; j < chars[i].size(); j++) {
			cout << chars[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	// solve
	int index = 0;
	vector<string> lcs(1);
	buildLCS(table, chars, m - 1, n - 1, lcs, index);
	cout << endl;

	// solutions
	cout << "solution(s): " << endl;
	for (int i = 0; i < lcs.size(); i++) {	
		cout << "\n\t";
		for (int j = lcs[i].length() - 1; j >= 0; j--) {
			cout << lcs[i][j];
		}
	}

    return 0;
}

void buildLCS(vector<vector<int>>& table, vector<vector<char>>& characters, int i, int j, vector<string>& results, int& index) {
	
	bool done = false;
	int current_instance_index = index;	
	while (i >= 0 && j >= 0 && !done) {	

		if (characters[i][j] == '+') {

			// allows follow greatest path
			int up = table[i][j+1];
			int left = table[i+1][j];

			// stop condition
			if (i == -1 || j == -1) { done = true; }

			// go left
			if (left > up && left == table[i+1][j+1]) {
				j--;
				continue;
			}

			// go up
			if (up > left && up == table[i+1][j+1]) {
				i--;
				continue;
			}

			// both
			if (up == left) {

				// start a new LCS builder if there are two possible ways (new instance handles way up)
				if (characters[i-1][j] != '+' || characters[i][j-1] != '+') {
					results.push_back(results[current_instance_index]);
					index++;
					buildLCS(table, characters, i-1, j, results, index);
				}

				// current instance handles way left
				j--;
			}
		}
		else {
			results[current_instance_index].append(sizeof(char), characters[i][j]);
			cout << "added " << characters[i][j] << endl; 

			// go diagonally
			i--;
			j--;
		}
	}
}