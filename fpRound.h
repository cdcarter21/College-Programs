#include <cstdint>
#include <string>
#include <iostream>
#include <bitset>
#include <cmath>

class FP {
    uint64_t    significand;
    uint32_t    exponent;
    bool        sign;
    uint8_t     significand_size;
    uint8_t     exponent_size;
public:
    FP (const FP &other)
    {
        significand = other.significand;
        exponent = other.exponent; 
        sign = other.sign; 
        significand_size = other.significand_size;
        exponent_size = other.exponent_size; 
    }
    FP(int s,int e)
    {
        significand_size = s; 
        exponent_size = e; 
        sign = true; 
        //i created a private utility function for this so I can create
        //a NaN within my string constructor. 
        createNaN(); 
    }
    FP(int s,int e,int x)
    {
        significand_size = s; 
        exponent_size = e;    
        sign = true;  
        //if the number is zero    
        if (x == 0)
        {
            significand = 0;
            exponent = 0;
            sign = true; 
            return; 
        }
        //if the number is negative
        if (x < 0)
        {
            sign = false; 
            x = abs(x);
        }
        //set exponent to exponent offset
        exponent = (1 << (exponent_size - 1)) - 1 ; // 2^(exponent_size - 1) - 1
        //set T to number
        int test = x; 
        //as long as T > 0, shift T right and increment exponent
        while (test > 1) 
        {
            test = test >> 1; 
            exponent++; 
        }
        //if exponent >= mask, the number is infinite
        unsigned int exponent_mask = (1 << exponent_size) - 1; 
        if (exponent >= exponent_mask) 
        {
            exponent = exponent_mask; 
            significand = 0; 
            return; 
        }
        //set T to number
        uint64_t newTest = (uint64_t)x; 
        //while T > largest significand, shift T right
        uint64_t largest = ((uint64_t)1 << (significand_size + 1)) - 1; 
        while (newTest > largest)
        {
            newTest = newTest >> 1; 
        }
        //while hidden bit of T is set, shift T left
        uint64_t hidden_bit = uint64_t(1) << significand_size;
        while (newTest < hidden_bit) 
        {
            newTest = newTest << 1; 
        }
        //set significand to T but with hidden bit removed
        significand = newTest & (hidden_bit - 1);
        return; 
    }
    FP(int s,int e,std::string x)
    {
        significand_size = s; 
        exponent_size = e; 
        if (x[0] == '+')
            sign = true; 
        else if (x[0] == '-')
            sign = false; 
        else if (x[0] != '+' || x[0] != '-') {
            createNaN(); 
            return; 
        }
        if (x[1] == 'N' && x[2] == 'A' && x[3] == 'N') {
            createNaN(); 
            return; 
        }
        if (x[1] == 'I' && x[2] == 'N' && x[3] == 'F') {
            exponent = 0; 
            for (int count = 0; count < exponent_size; count++) {
                exponent = exponent | (1 << count);
            }
            significand = 0; 
            return; 
        }
        if (x[1] != '1' && x[1] != '0') {
            createNaN(); 
            return; 
        }
        if (x.length() == 2 && x[1] == '0') {
            exponent = 0; 
            significand = 0; 
            return; 
        }
        int length = x.length(); 
        std::string sig = "";
        std::string exp = "";
        int count = 3; 
        while (count < length) {
            if (x[count] == 'b') {
                count++;
                break; 
            }
            if (x[count] != '0' && x[count] != '1') {
                std::cout << "error: x[count] = " << x[count] << "\n";
                return; 
            }
            sig += x[count];
            count++; 
        }
        int digits = count - 3; 
        while (digits <= significand_size) {
            sig += '0'; 
            digits++; 
        }
        while (count < length) {
            exp += x[count];
            count++;
        }
        int expLength = exp.length();
        if (expLength > e) {
            std::cout << "exp too large\n";
            return; 
        }
        int bias = (1 << (e - 1)) - 1;
        exponent = stoi(exp) + bias;
        int intExp = stoi(exp) + bias;
        int sigLength = sig.length();   

        //converting string to uint_64
        int64_t decimal = 0; 
        int power = 0; 
        for (int i = sigLength-1; i>=0; i--) {
            if (sig[i] == '1')
                decimal += pow(2, power);
            power++; 
        }
        significand = decimal; 

        //if the significand passed in is too many bits
        int iteration = 0; 
        while (sigLength > s) {
            sig.pop_back();
            sigLength--; 
            intExp--; 
            iteration++; 
            //if we are subnormal
            if (intExp <= 0)  {
                //this is the case where we can't store the number
                if (iteration == 1) 
                    significand = 0; 
                exponent = 0; 
                return; 
            }
        }

        //add hidden bit if it's there
        uint64_t hidden_bit = 1ULL << significand_size;
        if (x[1] == '1')  
            significand += hidden_bit; 

        while (intExp <= 0) {
            significand >>= 1; 
            intExp++; 
        }

        //if S is too large, shift it right and increment E
        uint64_t largest = 1ULL << (significand_size+1);
        if (significand >= largest) {
            while (significand >= largest)
            {
                significand >>= 1; 
                intExp++; 
                exponent++; 
            }
            //if we become subnormal
            if (intExp < 0) {
                significand >>= 1; 
                exponent = 0; 
                return; 
            }
            else
                significand &= (hidden_bit - 1);
            return; 
        }

        //while leading one isn't present, shift left
        while (significand < hidden_bit) {
            //if we become subnormal
            if (intExp <= 0) {
                significand >>= 1; 
                exponent = 0; 
                return; 
            }
            significand <<= 1; 
            intExp--; 
            exponent--; 
        }

        if (intExp == 0) {
            significand >>= 1; 
            exponent = 0; 
        }
        else 
            significand &= (hidden_bit-1); 
    }

    bool isNaN() const
    {
        if (exponent == 0 || significand == 0)
            return false; 

        uint32_t exp = exponent;
        uint64_t sig = significand; 
        int count = 0; 
        while (count < exponent_size) {
            if ((exp & 1) == 0)
                return false; 
            exp = exp >> 1; 
            count++; 
        }
        count = 0; 
        while (count < significand_size) {
            if ((sig & 1) == 1)
                return true; 
            sig = sig >> 1; 
            count++; 
        }
        return true; 
    }

    bool isZero() const
    {
        if (exponent == 0 && significand == 0)
            return true; 
        else 
            return false; 
    }

    bool isInfinity() const
    {
        if (exponent == 0 || significand != 0)
            return false;

        uint32_t exp = exponent;
        for (int i=exponent_size; i>0; i--) {
            if ((exp & 1) == 0)
                return false; 
            exp >>= 1; 
        } 
        return true;
    }
    bool isPositive() const
    {
        if (sign == true)
            return true; 
        else    
            return false; 
    }
    bool isNormal()
    {
        if (exponent == 0)
            return false;
        uint32_t exp = exponent;
        int count = 0; 
        while (count < exponent_size) {
            if ((exp & 1) == 0)
                return true; 
            exp = exp >> 1; 
            count++; 
        } 
        return false; 
    }
    bool isSubnormal()
    {
        if (exponent != 0 || significand == 0)
            return false; 
        else
            return true; 
    }

    std::string to_string()
    {
        std::string s = "";
        if (isPositive())
            s += '+';
        else
            s += '-';
        if (isNaN()) {
            s += "NAN";
            return s; 
        }
        if (isInfinity()) {
            s += "INF";
            return s; 
        } 
        if (isZero()) {
            s += '0';
            return s; 
        }
        if (isSubnormal())
            s += "0.";
        else 
            s += "1.";
        uint64_t sig = significand; 
        uint64_t bitmask = uint64_t(1) << (significand_size-1); 
        for (int count = significand_size; count > 0; count--) {
            if (bitmask & sig) 
                s += '1';
            else
                s += '0';
            bitmask = bitmask >> 1; 
        }
        while (s.back() == '0')
            s.pop_back(); 
        s += 'b';
        int bias = (1 << (exponent_size - 1)) - 1;
        int ex = exponent - bias; 
        if (ex >= 0)
            s += '+';
        s += std::to_string(ex); 
        return s; 
    }

    bool addOne() {
        //if it's NaN or Infinity, we know we can't add 1
        if (isNaN() || isInfinity()) {
            return false;
        }

        uint64_t maxSignificand = (uint64_t(1) << significand_size) - 1;
        int32_t expOne = 0; 
        int64_t sigOne = (int64_t)1 << significand_size; 
        int bias = (1 << (exponent_size - 1));
        int ex = exponent - bias;
        //if the real exponent is bigger than the exponent of 1.0
        if (ex > expOne) {
            sigOne = sigOne >> (exponent - expOne);
            if ((significand + sigOne) > maxSignificand)
                return false; 
            else {
                significand += sigOne; 
                return true; 
            }
        }
        //it's zero
        else {
            exponent = bias; 
            return true; 
        }
    }

    void negate() { sign = !sign; }

    enum Order { BEFORE, EQUAL, AFTER, UNORDERED }; 
    Order compare(const FP &other) 
    {
        //exception cases
        if (isNaN() || other.isNaN()) {
            // std::cout << "isNaN\n";
            return UNORDERED; 
        }
        if (isZero() && other.isZero()) {
            // std::cout << "isZero\n";
            return EQUAL; 
        }
        //easy sign cases
        if (sign == false && other.sign == true) {
            // std::cout << "false true\n";
            return BEFORE; 
        }
        if (sign == true && other.sign == false) {
            // std::cout << "true false\n";
            return AFTER; 
        }

        //compare exponents 
        if (exponent > other.exponent) {
            if (sign == true) {
                // std::cout << "exp true\n";
                return AFTER; 
            }
            else {
                // std::cout << "exp false\n";    
                return BEFORE; 
            }
        }
        if (exponent < other.exponent) {
            if (sign == true) {
                // std::cout << "less exp true\n";
                return BEFORE; 
            }
            else {
                // std::cout << "les exp false\n"; 
                return AFTER; 
            }
        }
        //compare significands 
        if (significand > other.significand) {
            if (sign == true) {
                // std::cout << "big sig true\n";
                return AFTER;
            }
            else {
                // std::cout << "big sig false\n"; 
                return BEFORE; 
            }
        }
        if (significand < other.significand) {
            if (sign == true) {
                // std::cout << "less sig true\n";
                return BEFORE; 
            }
            else {
                // std::cout << "less sig false\n"; 
                return AFTER; 
            }
        }
        else
            return EQUAL; 
    }

    enum RoundMode { ZERO, UP, DOWN, NEAR_EVEN, NEAR_AWAY };

    uint64_t ulp_dist(const FP &other)
    {
        if (isZero() && other.isZero())
            return 0; 

        int sigDiff = 0; 
        //my significand is bigger
        if (significand > other.significand) {
            sigDiff = significand - other.significand;
            //if my exponent is smaller, we want to subtract
            //this difference at the end
            if (exponent < other.exponent)
                sigDiff = -sigDiff; 
        }
        //my significand is smaller
        else {
            sigDiff = other.significand - significand; 
            //if my exponent is bigger, we want to subtract
            //this difference at the end
            if (other.exponent < exponent)
                sigDiff = -sigDiff; 
        }
        //calculate difference in exponents 
        int expDiff = abs(exponent - other.exponent);

        return (expDiff * (1 << significand_size)) + sigDiff; 
    }
    void add(const FP &other) 
    {
        //any add with a NaN results in a NaN 
        if (isNaN() || other.isNaN()) {
            createNaN(); 
            return; 
        }
        //if we know we are adding zero, we just stay ourself
        if (other.isZero()) 
            return; 
        //if I am zero, we know i will just be what he is
        if (isZero()) {
            sign = other.sign;
            exponent = other.exponent;
            significand = other.significand;
            return;
        }

        //X
        bool signX = sign; 
        int32_t expX = exponent; 
        int64_t sigX = significand; 

        //Y
        bool signY = other.sign; 
        int32_t expY = other.exponent; 
        int64_t sigY = other.significand; 

        //set F to sign of X
        bool f = signX; 
        int expDiff = abs(expX - expY);

        //if |X| = |Y| and have diff signs, the answer is 0
        if (expX == expY && sigX == sigY && signX != signY) {
            exponent = 0;
            significand = 0;
            return; 
        }
        //if |X| < |Y| set F to the sign of Y and swap X and Y 
        if (expX < expY || (expX == expY && sigX < sigY)) {
            f = signY; 
            signY = signX; 
            expY = expX; 
            sigY = sigX; 

            signX = other.sign; 
            expX = other.exponent; 
            sigX = other.significand; 
        }
        //shift Y's significand to right, based off diff in exponents
        if (expY != 0)
            sigY += (1ULL << significand_size); //adding hidden 1 to our sig
        sigY >>= expDiff;

        //set E to X's exponent 
        int32_t e = expX; 
        if (expX != 0)
            sigX += (1ULL << significand_size); //adding hidden 1 to our sig
        //set S to X + Y if signs are equal, or X - Y if diff signs
        if (signX == signY) 
            significand = sigX + sigY; 
        else 
            significand = sigX - sigY; 

        //if S is zero, the answer is zero. 
        if (significand == 0) {
            sign = f; 
            exponent = e; 
            significand = 0; 
            return; 
        }

        //if S is too large, shift it right and increment E
        uint64_t largest = 1ULL << (significand_size+1);
        while (significand >= largest)
        {
            significand >>= 1; 
            e++; 
        }
        //while S doesn't have 1 in the "hidden" bit, shift it left and decrement E
        uint64_t hidden_bit = 1ULL << significand_size;
        while (significand < hidden_bit) 
        {
            significand <<= 1; 
            e--; 
        }
        //F, E, and masked-off S are the final answer.
        sign = f; 
        exponent = e; 
        significand &= (hidden_bit - 1);
        return; 

    }
    void add(const FP &other, RoundMode mode)
    {
        //any add with a NaN results in a NaN 
        if (isNaN() || other.isNaN()) {
            createNaN(); 
            return; 
        }
        //if we know we are adding zero, we just stay ourself
        if (other.isZero()) 
            return; 
        //if I am zero, we know i will just be what he is
        if (isZero()) {
            sign = other.sign;
            exponent = other.exponent;
            significand = other.significand;
            return;
        }
        if (isInfinity() && other.isInfinity()) {
            createNaN(); 
            return; 
        }
        if (isInfinity()) return; 
        if (other.isInfinity()) {
            sign = other.sign; 
            exponent = other.exponent; 
            significand = other.significand; 
            return; 
        }
        // bool sub = false; 
        // if (exponent == 0 || other.exponent == 0)
        //     sub = true; 

        // bool allSub = false; 
        // if (exponent == 0 && other.exponent == 0)
        //     allSub = true; 
        //X
        bool signX = sign; 
        int32_t expX = exponent; 
        int64_t sigX = significand; 

        // std::cout << "sigX: " << std::bitset<3>(sigX) << std::endl; 
        //Y
        bool signY = other.sign; 
        int32_t expY = other.exponent; 
        int64_t sigY = other.significand; 
        // std::cout << "sigY: " << std::bitset<3>(sigY) << std::endl; 
        //set F to sign of X
        bool f = signX; 
        int expDiff = abs(expX - expY);

        //if |X| = |Y| and have diff signs, the answer is 0
        if (expX == expY && sigX == sigY && signX != signY) {
            exponent = 0;
            significand = 0;
            return; 
        }
        //if |X| < |Y| set F to the sign of Y and swap X and Y 
        if (expX < expY || (expX == expY && sigX < sigY)) {
            f = signY; 
            signY = signX; 
            expY = expX; 
            sigY = sigX; 

            signX = other.sign; 
            expX = other.exponent; 
            sigX = other.significand; 
        }

        

        int shiftAmount = expDiff; 
        if (expY == 0 && shiftAmount != 0)
            shiftAmount--; 
        std::cout << "shift: " << shiftAmount << std::endl; 
        // sigY <<= shiftAmount; 
        //shift Y's significand to right, based off diff in exponents
        if (expY != 0)
            sigY += (1ULL << significand_size); //adding hidden 1 to our sig
        // sigY >>= expDiff;
        std::cout << "sigY: " << std::bitset<6>(sigY) << std::endl; 

        //set E to X's exponent 
        std::cout << "sigX: " << std::bitset<6>(sigX) << std::endl; 
        int32_t e = expX; 
        if (expX != 0)
            sigX += (1ULL << significand_size); //adding hidden 1 to our sig
        // if (expY != 0)
            sigX <<= shiftAmount; 
        std::cout << "sigX: " << std::bitset<6>(sigX) << std::endl; 
        //set S to X + Y if signs are equal, or X - Y if diff signs
        // bool subtract = false; 
        if (signX == signY) {
            significand = sigX + sigY; 
        }
        else {
            // std::cout << std::bitset<3>(significand) << std::endl; 
            // std::cout << "sigX: " << std::bitset<3>(sigX) << std::endl; 
            // std::cout << "sigY: " << std::bitset<3>(sigY) << std::endl; 
            significand = sigX - sigY; 
            // subtract = true; 
            // std::cout << std::bitset<3>(significand) << std::endl; 
        }
        std::cout << "sig: " << std::bitset<6>(significand) << std::endl; 
        //if S is zero, the answer is zero. 
        if (significand == 0) {
            sign = f; 
            exponent = e; 
            significand = 0; 
            return; 
        }

        int sticky = 0; 
        int round = 0; 
        // if (!sub) {
            for (int i = shiftAmount; i > 0; i--) {
                if (significand & 1) {
                    if (i == 1)
                        round = 1; 
                    else 
                        sticky = 1; 
                }
                significand >>= 1; 
            }
        // }
        uint64_t hidden_bit = 1ULL << significand_size;
        
        
        // if (sub) {
        //     sign = f; 
        //     if (significand & hidden_bit) {
        //         exponent = 1; 
        //         significand &= (hidden_bit - 1);
        //         return; 
        //     }
        //     else if (subtract) {
        //         exponent = 0; 
        //         significand &= (hidden_bit - 1);
        //         return; 
        //     }
        //     else 
        //         exponent = e; 
        // }
        // std::cout << "sign: " << std::bitset<64>(significand) << std::endl;  
        // std::cout << "round: " << round << "; guard: " << guard << "; sticky: " << sticky << std::endl; 
        //if S is too large, shift it right and increment E
        uint64_t largest = 1ULL << (significand_size+1);
        // std::cout << "larg: " << std::bitset<64>(largest) << std::endl;  
        while (significand >= largest)
        {
            significand >>= 1; 
            e++; 
        }
        // std::cout << "sign: " << std::bitset<64>(significand) << std::endl;  
        int ulp = significand & 1; 
        //while S doesn't have 1 in the "hidden" bit, shift it left and decrement E
        // std::cout << "hidd: " << std::bitset<64>(hidden_bit) << std::endl;  
        while (significand < hidden_bit) 
        {
            if (e == 0) {
                //e++; 
                //significand >>= 1; 
                return; 
            }
            significand <<= 1; 
            e--; 
            if (e == 0) {
                significand >>= 1; 
                exponent = 0; 
                return; 
            }
        }
        // else {
        //     exponent = e; 
        //     significand &= (hidden_bit - 1);
        //     return; 
        // }
        // else {
        //     if (significand & hidden_bit)
        //         significand >>= 1; 
        // }
        if (mode == UP && (round || sticky))
            significand++; 
        else if (mode == DOWN && !sign && (round || sticky))
            significand++; 
        else if (mode == NEAR_EVEN || mode == NEAR_AWAY) {
            if (round && sticky)
                significand++;
            else if (round && !sticky) {
                if (mode == NEAR_EVEN) {
                    if (ulp)
                        significand++; 
                }
                else 
                    significand++; 
            }
        }
        //F, E, and masked-off S are the final answer.
        if (e == 0 && (significand & hidden_bit))
            e = 1; 

        sign = f; 
        exponent = e; 
        significand &= (hidden_bit - 1);
        // std::cout << "sign: " << std::bitset<64>(significand) << std::endl; 
        return; 
    }

    // for testing
    uint64_t    getSignificand()    const { return significand; }
    uint32_t    getExponent()       const { return exponent; }

private:
    //private utility function to create a NaN
    void createNaN() 
    {
        exponent = 0; 
        for (int count = 0; count < exponent_size; count++) {
            exponent = exponent | (1 << count);
        }
        significand = (significand & 0) + 1; 
    }
};