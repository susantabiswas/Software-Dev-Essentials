/*
    https://leetcode.com/problems/divide-two-integers/submissions/
*/
/*
    Solution using only 32 bit variables(trickier)
*/
class Solution {
public:
    int divide(int x, int y) {
        unsigned int divisor = static_cast<unsigned int>(y);
        unsigned int dividend = static_cast<unsigned int>(x);
        unsigned int quotient = 0;
        
        // decide the sign
        bool negative = (x < 0) ^ (y < 0);
        if(dividend == INT_MIN  && divisor == -1)
            return INT_MAX;
        if(y < 0) 
            divisor = -1 * divisor;
        if(x < 0)
            dividend = -1 * dividend;
        
        // We start with the largest permissible multiple for the divisor
        // such that the divisor is still smaller than dividend,
        // then we add that bit to the quotient. The dividend is updated 
        // with dividend = dividend - divisor*multiple
        // Then we again find the next largest multiple that when multiplied with divisor
        // gives a value closer to dividend. Continue doing this till we get 0
        const int N_BITS = sizeof(int) * 8;
        
        // find the MSB set bit(1 indexed)
        int msb_pos = 0;
        for(int i = N_BITS - 1; i >= 0; i--) {
            if((1 << i) & divisor) {
                msb_pos = i + 1;
                break;
            }
        }
        
        for(int i = (N_BITS - msb_pos); i >= 0; i--) {
            // 2^i * divisor <= dividend
            if((divisor << i) <= dividend) {
                dividend -= divisor << i;  // dividend = dividend - divisor*2^i
                quotient |= 1 << i;
            }
        }
        
        // check for overflow, happens when the quotient is storing max value
        // which in case negative sign is not there, needs to be made +ve and that
        // time overflow happens, quotient = INT_MIN and nagtive = false
        if(quotient == numeric_limits<int>::min() && !negative)
            return numeric_limits<int>::max();
        // add the sign if required
        quotient = negative ? -1 * quotient: quotient;

        return quotient; 
      }
};

// Solution using long long int
class Solution {
public:
    int divide(int x, int y) {
        long long divisor = static_cast<long long>(y);
        long long dividend = static_cast<long long>(x);
        long long quotient = 0;
        
        // decide the sign
        bool negative = (x < 0) ^ (y < 0);
        divisor = abs(divisor), dividend = abs(dividend);
        
        // We start with the largest permissible multiple for the divisor
        // such that the divisor is still smaller than dividend,
        // then we add that bit to the quotient. The dividend is updated 
        // with dividend = dividend - divisor*multiple
        // Then we again find the next largest multiple that when multiplied with divisor
        // gives a value closer to dividend. Continue doing this till we get 0
        const int N_BITS = sizeof(int) * 8;
        for(int i = N_BITS - 1; i >= 0; i--) {
            // 2^i * divisor <= dividend
            if((divisor << i) <= dividend) {
                dividend -= divisor << i;  // dividend = dividend - divisor*2^i
                quotient |= 1LL << i;
            }
        }
        // add the sign if required
        quotient = negative ? -1 * quotient: quotient;

        // check for overflow
        if(quotient > numeric_limits<int>::max())
            quotient = numeric_limits<int>::max();
        return static_cast<int>(quotient); 
    }
};
