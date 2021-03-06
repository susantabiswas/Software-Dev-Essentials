/*
    https://leetcode.com/problems/power-of-four/submissions/
    
    Sol1:
        Using logarithm, taking log with base 4 gives the 
        power p in 4^p.
        
    Sol2:
        Using bit manipulation.
        Numbers of the form 4^p, will have only one set bit and that too in even positions(0-indexed).
*/

class Solution {
public:
    int logSolution(int &num) {
        double p = log(num) / log(4);
        double diff = abs(p - floor(p));
        return diff < numeric_limits<double>::epsilon();        }
    
    int bitSolution(int &num) {
        int n_bits = sizeof(num) * 8;
        // A number which is a  power of 4 is also power
        // of 2, which means we can have only one set bit 
        // in the entire bit representation. Moreover the numbers which are power of 4 needs to be at the even positions (0 based index) i.e 0, 2, 4, ......
        int set_bits = 0;
        
        // check all the odd positions if there is a set bit
        for(int i = 0; i < n_bits; i += 1) {
            // check bit on odd pos.
            if(i % 2 && (num & (1 << i))) 
                return false;
            set_bits += (num & (1 << i)) ? 1 : 0;
            if(set_bits > 1)
                return false;
        }
        return set_bits == 1;
    }
    
    bool isPowerOfFour(int num) {
        // return logSolution(num);
        return bitSolution(num);
    }
};
