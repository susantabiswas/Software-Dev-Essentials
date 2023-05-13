/*
    https://leetcode.com/problems/minimize-xor/
    
    TC: O(32) ~ O(1)
    SC: O(1)
    
    Since we want to make x small, we need to ensure that it is as close as
    possible to num1.
    Since we are doing XOR, same bits becomes 0, so we set the bits in x at leftmost positions
    where bits are set in num1. By setting 1 in rightmost positions, we can ensure that XOR of 
    those positions give 0 and the number will become small.
    
    If we are still left with set bits, then we can set the positions from LSB where the original
    bit in num1 was 0, this ensures that the number is still small since we are setting the bits
    from rightmost position.
*/
class Solution {
public:
    int minimizeXor(int num1, int num2) {
        // No. of set bits
        int n_set = 0;
        // Total no. of bits
        int N_BITS = sizeof(num2) * 8;
        
        // find set bits in num2 using right shift
        while(num2) {
            if(num2 & 1)
                ++n_set;
            num2 >>= 1;
        }
        
        int x = 0;
        // Mask where the MSB is set 
        unsigned int mask = 1 << (N_BITS - 1);
        
        // Start from MSB and find all the 1s in num1, for each set bit
        // we can put a set bit in x
        for(int pos = N_BITS - 1; pos >= 0 && n_set > 0; pos--) {
            if(num1 & mask) {
                x |= mask;
                --n_set;
            }
            mask >>= 1;
        }
        
        // mask = 00....000001
        mask = 1;
        // Start from LSB and check for the rightmost unset bits,
        // we can set the bits there to keep x small
        for(int pos = 0; pos < (N_BITS - 1) && n_set > 0; pos++) {
            if(!(num1 & mask)) {
                x |= mask;
                --n_set;
            }
            mask <<= 1;
        }
        return x;
    }
};
