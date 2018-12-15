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
        uint field_length;
        uchar* needle;
        uint needle_length;

        // Constructors
        KnuthMorrisPratt(string filename, uchar* needle, uint length) : needle(needle), needle_length(length) {

            // Parse file to string
            ifstream in(filename);
            string contents((std::istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
            
            cout << "INITIALIZING VARIABLES" << endl;

            // Set length variables
            this->field_length = contents.length();

            // Set uchar* variables
            this->search_field = new char();
            strcpy(this->search_field, contents.c_str());
        };

        // Functions
        int start() {       

            cout << "KMP START" << endl;

            int aantal = 0;
            int found[100];
            int i = 0;
            int j = 0; 

            prefixFunction(this->needle, found);

            for (int i = 0; i < this->field_length; i++) {

                // CHARACTERS NOT EQUAL: reset (if not @ start)
                while (j > 0 && this->search_field[i] != this->needle[j]) {
                    j = found[j-1];
                }

                // CHARACTERS EQUAL: check next
                if (this->search_field[i] == this->needle[j]) {
                    j++;
                }

                // FOUND COMPLETE WORD: aantal++ & continue
                if (j == this->needle_length) {
                    aantal++;
                }
            }

            return aantal;
        };

        // When the pattern contains a part that repeats itself
        // You can't go back to the beginning of the pattern
        // Thats why we go back to the first repeating part
        /* EXAMPLE defdef 
         *          000123  => when no match at the second 'e', return to the first 'e'
         */
        void prefixFunction(const uchar* needle , int* found) {
           
            int i = 1;
            int j = 0;

            found[0] = 0;
            while (i < this->needle_length) { 
                if (needle[i] == needle[j]) {
                    found[i] = j+1;
                    i++;
                    j++;
                } 
                else if (j > 0) {
                    j = found[j-1];
                } 
                else {
                    found[i] = 0;
                    i++;
                }
            }

            for (int i = 0; i < this->needle_length; i++) {
                cout << found[i];
            }
            cout << endl;
        }
};
    