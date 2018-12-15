#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

/* Boyer Moore has 3 different methods
 * 
 * 1. using a two-dimensional table with all positions of a single character (original)
 * 2. the smallest location of a single character (Horspool)
 * 3. immediately calculate the smallest shift (Sunday)
 * 
 * This is a Sunday implementation
 */
class Boyer_Moore {

    public:

        // Fields
        char* text;
        uint text_length;
        uchar* pattern;
        uint pattern_length;

        // Constructors
        Boyer_Moore(string filename, uchar* pattern, uint length) : pattern(pattern), pattern_length(length) {

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

            // intialize bad-character table
            map<char, int> table;
            buildBadCharacterTable(this->pattern, this->pattern_length, table);

            // start algorithm (boyer-moore start at the end of the pattern)
            int matches = 0;
            int field_index = this->pattern_length - 1;
            int pattern_index = this->pattern_length - 1;
            while (field_index < this->text_length) {
                // equal: decrement both indexes
                if (this->pattern[pattern_index] == this->text[field_index]) {
                    field_index--;
                    pattern_index--;
                }
                // not equal: find character in bad-character table and shift with that value (if not found, the pattern length)
                else {
                    char current_character = this->text[field_index];
                    if (table.find(current_character) != table.end()) {
                        field_index += table[current_character];
                    }
                    else {
                        field_index += this->pattern_length;
                    }
                }

                if (pattern_index == 0) {
                    matches++;

                    pattern_index = this->pattern_length - 1;
                    field_index += this->pattern_length;
                }
            }

            // do last check
            while (pattern_index != 0 && this->pattern[pattern_index] == this->text[field_index]) {
                field_index--;
                pattern_index--;
            }
            if (pattern_index == 0) { matches++; }

            // done
            return matches;

        };

        void buildBadCharacterTable(const uchar* pattern, uint pattern_length, map<char, int>& table) {
            for (int index = 0; index < pattern_length; index++) {
                char character = pattern[index];
                int shift = max(1, (int)pattern_length - index - 1);
                
                auto iter = table.find(character);
                if (iter != table.end()) {
                    // get the minimum shift. because we loop from left to right: shift becomes automatically smaller and overwriting is valid
                    /* table[character] = min(table[character], shift); */
                    table[character] = shift;
                }
                else {
                    table.insert(pair<char, int>(character, shift));
                }
            }
        };
};
    