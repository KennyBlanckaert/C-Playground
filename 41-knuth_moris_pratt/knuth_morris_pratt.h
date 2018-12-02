#include <queue>
#include <cstring>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

class KnuthMorrisPratt {

    public:

        // Fields
        char* search_field;
        int field_length;
        char* needle;
        int needle_length;

        // Constructors
        KnuthMorrisPratt(string filename, const char* needle, uint length) {
            ifstream in(filename);
            string contents((std::istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
            
            cout << "INITIALIZING VARIABLES" << endl;
            this->field_length = contents.length();
            this->needle_length = length;

            this->search_field = (char*) malloc(sizeof(char*) * this->field_length);
            strcpy(this->search_field, contents.c_str());

            this->needle = (char*) malloc(sizeof(char*) * this->needle_length);
            strcpy(this->needle, needle);
        };

        // Functions
        int start() {       

            cout << "KMP START" << endl;

            int aantal = 0;
            int found[100];
            int i = 0;
            int j = 0; 

            FailureFunction(this->needle, found);

            for (int i = 0; i < this->field_length; i++) {

                // CHARACTERS NOT EQUAL: reset found (if not @ start)
                while (j > 0 && this->search_field[i] != this->needle[j]) {
                    j = found[j-1];
                }

                // CHARACTERS EQUAL: check next
                if (this->search_field[i] == this->needle[j]) {
                    j++;
                }

                // VOLLEDIG WOORD GEVONDEN: aantal++ & verder zoeken
                if (j == this->needle_length) {
                    aantal++;
                }
            }

            return aantal;
        };

        void FailureFunction(char* pattern , int* found) {
           
            int i = 1;
            int j = 0;

            found[0] = 0;
            while (i < this->needle_length) { 
                if (pattern[i] == pattern[j]) {
                    found[i] = j+1;
                    i++;
                    j++;
                } 
                else if (j>0) {
                    j = found[j-1];
                } 
                else {
                    found[i] = 0;
                    i++;
                }
            }
}
};
    