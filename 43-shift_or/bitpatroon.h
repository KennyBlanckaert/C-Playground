class Bitpatroon {
    public:

        // Fields
        uint bits;
        uint pattern_length;

        // Constructor
        Bitpatroon(uint u=0):bits(u) { };

        // Setters
        void setLength(uint needle_length) {
            this->pattern_length = needle_length;
        }

        //AND operator
        const Bitpatroon operator&(const Bitpatroon& b) const {
            return Bitpatroon(bits & b.bits);
        };

        //OR operator
        const Bitpatroon operator|(const Bitpatroon& b) const {
            return Bitpatroon(bits | b.bits);
        };

        //AND= operator
        const Bitpatroon& operator&=(const Bitpatroon& b){
            bits&= b.bits;
            return *this;
        };

        //OR= operator
        const Bitpatroon& operator|=(const Bitpatroon& b){
            bits |= b.bits;
            return *this;
        };

        //logische operatoren
        bool andOperation(const Bitpatroon& b) const{
            return (bits & b.bits)!=0;
        };

        bool orOperation(const Bitpatroon& b) const{
            return (bits | b.bits)!=0;
        };

        //let op: shiftoperaties verplaatsen niets als shift >= pattern_length.
        const Bitpatroon shiftLeft(uint shift) const{
            return Bitpatroon(bits<<shift);
        };

        const Bitpatroon shiftRight(uint shift) const{
            return Bitpatroon(bits>>shift);
        };

        // bitpatroon met 1-bit op gegeven positie
        // u = ...3210
        static Bitpatroon oneBit(uint u){
            return Bitpatroon(uint(1)<<(u - 1));
        };

        static Bitpatroon orPattern(uchar character, const uchar* needle, uint length) {
            
            uint firstBit = (needle[0] == character ? 0 : 1);
            Bitpatroon b(firstBit);
            
            for (uint i = 1; i < length; i++) {
                if (needle[i] != character) {
                    b = b.shiftLeft(1);
                    b.bits |= 0x01;
                }
                else {
                    b = b.shiftLeft(1);
                }
            }

            return b;
        }

        friend ostream& operator<<(ostream& os, const Bitpatroon& b){
            for (int i = 0; i < b.pattern_length; i++) {
                os << b.andOperation(oneBit(b.pattern_length - i));
            }

            return os;
        };
};
    
