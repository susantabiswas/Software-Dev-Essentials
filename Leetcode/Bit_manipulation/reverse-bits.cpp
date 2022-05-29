/*
    https://leetcode.com/problems/reverse-bits/
    
    Start processing the LSB of orig number by doing a right shift on it.
    Put each of the LSB of orig number to the rev number's LSB and next time do
    a left shift to imitate order reversal.
    TC: O(1) 
    SC: O(1)
*/
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        int rev = 0;
        // total npo. of bits in number
        int n_bits = sizeof(n) * 8;
        
        for(int i = 0; i < n_bits; i++) {
            // right shift to make room for 1 bit at LSB
            rev <<= 1;
            // get the LSB bit of orig num and put it at LSB or reverse number
            rev |= (n & 1);
            n >>= 1;
        }
        return rev;
    }
};
