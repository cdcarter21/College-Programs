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
//took off the -1 at the end:
        exponent = (1 << (exponent_size - 1)) ; // 2^(exponent_size - 1) - 1
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
            //exponent--; 
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
        //need to change if we support subnormal #'s
        if (x[1] == '0') {
            exponent = 0; 
            significand = 0; 
            return; 
        }
        if (x[1] != '1') {
            createNaN(); 
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
        int bias = (1 << (e - 1));
        exponent = stoi(exp) + bias;
        int sigLength = sig.length();   
        if (sigLength > s) {
            std::cout << "sig too large\n";
            return; 
        }
        int64_t decimal = 0; 
        int power = 0; 
        for (int i = sigLength-1; i>=0; i--) {
            if (sig[i] == '1')
                decimal += pow(2, power);
            power++; 
        }
        significand = decimal; 
    }

    bool isNaN()
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

    bool isZero()
    {
        if (exponent == 0 && significand == 0)
            return true; 
        else 
            return false; 
    }

    bool isInfinity()
    {
        if (exponent == 0 || significand != 0)
            return false;

        uint32_t exp = exponent;
        while (exp > 0) {
            if ((exp & 1) == 0)
                return false; 
            exp = exp >> 1; 
        } 
        return true; 
    }
    bool isPositive()
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
        int bias = (1 << (exponent_size - 1));
        int ex = exponent - bias; 
        if (ex >= 0)
            s += '+';
        else
            s += '-';
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