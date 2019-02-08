typedef unsigned int uint;
typedef unsigned char uchar;

#include "bitpatroon.h"

/* create an S-table => each letter is converted to a pattern (1 if equal, 0 if not equal)
 * 
 * Algorithm
 *      start with ...0000
 *      shift + AND with pattern in S-tabel corresponding to the current character (not in table = AND with ...0000)
 *      when result equals ...0001 => MATCH
 */
class Shiftand {
    public:

        // Constructor
        Shiftand(const uchar* needle, uint needle_length) {
            this->needle = needle;
            this->needle_length = needle_length;

            // This loop creates a pattern for every character in the needle
            // NOTE: use |= to add a ONE-bit to an already existing pattern  
            // FOR EXAMPLE: needle = "where"
            //                  w: 10000
            //                  h: 01000
            //                  e: 00100
            //                  r: 00010
            //                  e: 00101
            for (uint i = 0; i < needle_length; i++) {
                uint characterIndex = (uint) needle[i];
                characterPatterns[characterIndex].setLength(needle_length);
                characterPatterns[characterIndex] |= Bitpatroon::oneBit(needle_length - i);
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

            // Start = ...0000
            Bitpatroon R(0);
            for (uint i = 0; i < search_field_length; i++) {

                // Right shift (1 is added to the left)
                R  = R.shiftRight(1);
                R |= Bitpatroon::oneBit(this->needle_length);           // not exist = ...0000

                // AND 
                uint characterIndex = (uint) search_field[i];            
                R &= characterPatterns[characterIndex];                

                // When R equals 1 => word match
                if (R.bits == 1) {
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
    
