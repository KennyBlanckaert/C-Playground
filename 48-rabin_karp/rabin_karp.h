#include <string>
#include <functional>
#include <algorithm>
#include <map>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

class Rabin_Karp {

    public:

        // Fields
        string text;
        uint text_length;
        string pattern;
        uint pattern_length;

        // Constructors
        Rabin_Karp(string filename, string pattern, uint length) : pattern(pattern), pattern_length(length) {

            // Parse file to string
            ifstream in(filename);
            string contents((std::istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
            this->text = contents;

            // Set length variable
            this->text_length = contents.length();
        };

        // Functions
        int start() {      

            // Used existing c++ hashing function
            // Try to create your own to make it even faster
            // (construct hashfunction for the alfabet that is used)
            // Only usefull if (hashing + hash compare) 'is faster than' (string compare)
            int matches = 0;
            int difference = (this->text_length - this->pattern_length);            
            hash<string> rabin_karp_hash_function;
            size_t pattern_hash = rabin_karp_hash_function(this->pattern);
            for (int pos = 0; pos <= difference; pos++) {
                size_t text_substr_hash = rabin_karp_hash_function(this->text.substr(pos, this->pattern_length));

                if (pattern_hash == text_substr_hash) {
                    matches++;
                    cout << "match found starting at character " << pos << endl;
                }
            }
            cout << endl;

            return matches; 
            
        };
};
    