#include <queue>
#include <cstring>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

class Boyer_Moore {

    public:

        // Fields
        char* search_field;
        uint field_length;
        uchar* needle;
        uint needle_length;

        // Constructors
        BoyerMoore(string filename, uchar* needle, uint length) : needle(needle), needle_length(length) {

            // Parse file to string
            ifstream in(filename);
            string contents((std::istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
            
            cout << "INITIALIZING VARIABLES" << endl;

            // Set length variable
            this->field_length = contents.length();

            // Set uchar* variable
            this->search_field = new char();
            strcpy(this->search_field, contents.c_str());
        };

        // Functions
        int start() {       

            cout << "Boyer Moore START" << endl;

        };

        // When the pattern contains a part that repeats itself
        // You can't go back to the beginning of the pattern
        // Thats why we go back to the first repeating part
        /* EXAMPLE defdef 
         *          000123  => when no match at the second 'e', return to the first 'e'
         */
        void buildBadCharacterTable(const uchar* needle, map<char, int>& table) {
           
        }
};
    