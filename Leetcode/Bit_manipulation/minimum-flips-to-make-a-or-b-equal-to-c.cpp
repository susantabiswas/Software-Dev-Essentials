/*
    https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/
    
    SOLUTION 1: 
    Iterate through the bit positions for all the numbers from right to left.
    For each bit of c, figure out if flip required in a and b
    
    TC: O(n), n = no. of bits in number
    SC: O(1)
    
    SOLUTION 2: 
    Just another style, here we shift the numbers right and always compare the
    LSB bit for figuring out if a flip is required
*/
class Solution {
public:
    // SOLUTION 1
    int solution1(int a, int b, int c) {
        int nBits = sizeof(c) * 8;
        int flips = 0;
        
        int pos = 1;
        // Iterate through all the bit positions from right to left
        for(int bit = 0; bit < nBits; bit++) {
            // find the bit for each of the numbers at `bit` position
            int aBit = a & pos;
            int bBit = b & pos;
            int cBit = c & pos;
            
            // If the bit in c = 0, then flip required if a and b have 1 set
            if(cBit == 0) {
                if(aBit)
                    ++flips;
                if(bBit)
                    ++flips;
            }
            // If bit in c = 1, just need 1 set bit in either a or b 
            else if(cBit && !(aBit | bBit))
                ++flips;
            
            pos <<= 1;
        }
        return flips;
    }
    
    // SOLUTION 2
    int solution2(int a, int b, int c) {
        int flips = 0;
        
        // right shift all the numbers and compare the LSB 
        // each time
        while(a || b || c) {
            if(c & 1) 
                flips += ((a & 1) || (b & 1)) ? 0 : 1;
            else
                flips += (a & 1) + (b & 1);
            
            a >>= 1;
            b >>= 1;
            c >>= 1;
        }
        return flips;
    }
    
    int minFlips(int a, int b, int c) {
        // return solution1(a, b, c);
        return solution2(a, b, c);
    }
};
