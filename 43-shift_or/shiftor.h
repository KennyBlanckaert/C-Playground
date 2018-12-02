typedef unsigned int uint;
typedef unsigned char uchar;

#include "bitpatroon.h"

/* create an S-table => each letter is converted to a pattern (1 if equal, 0 if not equal)
 * 
 * Algorithm
 *      start with ...1111
 *      shift + OR with pattern in S-tabel corresponding to the current character (not in table = OR with ...1111)
 *      when result equals ...1110 => MATCH
 */
class Shiftor {
    public:

        // Constructor
        Shiftor(const uchar* needle, uint needle_length) {
            this->needle = needle;
            this->needle_length = needle_length;

            // This loop creates a pattern for every character in the needle 
            // FOR EXAMPLE: needle = "where"
            //                  w: 01111
            //                  h: 10111
            //                  e: 11010
            //                  r: 11101
            //                  e: 11010
            for (uint i = 0; i < needle_length; i++) {
                uint characterIndex = (uint) this->needle[i];
                characterPatterns[characterIndex].setLength(this->needle_length);
                characterPatterns[characterIndex] |= Bitpatroon::orPattern(needle[i], this->needle, this->needle_length);
            }

            printTable();
        };

        // Prints S-tabel
        void printTable() {
            cout << "S-tabel: " << endl << endl;
            for (uint i = 0; i < this->needle_length; i++) {
                uint characterIndex = (uint) this->needle[i];
                cout << "\t" << this->needle[i] << ": " << characterPatterns[characterIndex] << endl;
            }
            cout << endl;
        };

        int search(std::queue<const uchar*>& position, const uchar* search_field, uint search_field_length) {           
            int occurences = 0;

            // Start = ...1111
            Bitpatroon R(1);
            R = R.shiftLeft(this->needle_length);
            R.bits -= 1;
            R.setLength(this->needle_length);

            for (uint i = 0; i < search_field_length; i++) {

                // Right shift (1 is added to the left)
                R = R.shiftRight(1);

                // OR
                uint characterIndex = (uint) search_field[i]; 
                if (characterPatterns[characterIndex].bits != 0) {
                    R |= characterPatterns[characterIndex];
                }    
                else {
                    Bitpatroon full_ones(1);                                // not exist = ...1111
                    full_ones = full_ones.shiftLeft(this->needle_length);
                    full_ones.bits -= 1;
                    R |= full_ones;
                }                      

                // When all bits are 1 except for the Least Significant Bit => match found
                if ((R.bits + 2) == (1<<this->needle_length)) {
                    position.push( &search_field[ i - this->needle_length + 1 ] );
                    occurences++;
                }
            }

            return occurences;
        };

    private:
        Bitpatroon characterPatterns[256];
        const uchar* needle;
        uint needle_length;
};
    
