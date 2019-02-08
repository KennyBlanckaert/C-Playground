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
        char* text;
        uint text_length;
        uchar* pattern;
        uint pattern_length;

        // Constructors
        KnuthMorrisPratt(string filename, uchar* pattern, uint length) : pattern(pattern), pattern_length(length) {

            // Parse file to string
            ifstream in(filename);
            string contents((std::istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

            // Set length variable
            this->text_length = contents.length();

            // Set uchar* variable
            this->text = new char();
            strcpy(this->text, contents.c_str());
        };

        // Functions
        int start() {       

            int aantal = 0;
            int found[100];
            int i = 0;
            int j = 0; 

            prefixFunction(this->pattern, found);

            for (int i = 0; i < this->text_length; i++) {

                // CHARACTERS NOT EQUAL: reset (if not @ start)
                while (j > 0 && this->text[i] != this->pattern[j]) {
                    j = found[j-1];
                }

                // CHARACTERS EQUAL: check next
                if (this->text[i] == this->pattern[j]) {
                    j++;
                }

                // FOUND COMPLETE WORD: aantal++ & continue
                if (j == this->pattern_length) {
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
        void prefixFunction(const uchar* pattern , int* found) {
           
            int i = 1;
            int j = 0;

            found[0] = 0;
            while (i < this->pattern_length) { 
                if (pattern[i] == pattern[j]) {
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

            // print prefix-code for verification
            cout << "prefixFunction: ";
            for (int i = 0; i < this->pattern_length; i++) {
                cout << found[i];
            }
            cout << endl << endl;
        }
};
    