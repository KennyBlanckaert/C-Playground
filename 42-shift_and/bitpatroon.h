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

        //EN-operator
        const Bitpatroon operator&(const Bitpatroon& b) const {
            return Bitpatroon(bits & b.bits);
        };

        //OF-operator
        const Bitpatroon operator|(const Bitpatroon& b) const {
            return Bitpatroon(bits | b.bits);
        };

        //EN-=-operator
        const Bitpatroon& operator&=(const Bitpatroon& b){
            bits&= b.bits;
            return *this;
        };

        //OF-=-operator
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

        friend ostream& operator<<(ostream& os, const Bitpatroon& b){
            for (int i = 0; i < b.pattern_length; i++) {
                os << b.andOperation(oneBit(b.pattern_length - i));
            }

            return os;
        };
};
    
