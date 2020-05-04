/*
	https://leetcode.com/problems/complement-of-base-10-integer/
	
	TC: O(b), b: no. of bits
	~O(32) ~O(1)
*/
class Solution {
public:
    int bitwiseComplement(int num) {
        if(num == 0)
            return 1;
        
        int complement = 0;
        int mask = 1, pos = sizeof(num) * 8 - 1;
        
        // find the position of first set bit( 0-indexed)
        while(!(num & (mask << pos))) {
            --pos;
        }
        
        // starting at the position of MSB, we put the complement
        // of bit at that position in original number
        while(pos >= 0) {
            // bit at pos-th position
            int bit = !(num & (mask << pos));
            complement |= (bit << pos--);
        }
        return complement;
    }
};
