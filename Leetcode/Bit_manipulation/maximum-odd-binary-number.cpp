/*
    https://leetcode.com/problems/maximum-odd-binary-number/

    TC: O(n)
    SC: O(1), no extra space other than the final string
    
    Find the no. of 1s. To make a string odd, set the LSB and then to make
    it bigger, start setting from MSB
*/
class Solution {
public:
    string maximumOddBinaryNumber(string s) {
        int ones = 0;
        for(auto ch: s)
            ones += (ch - '0');
        
        string max_odd(s.size(), '0');
        
        // set 1s from left and keep one for the LSB
        if(ones) {
            max_odd.back() = '1';
            --ones;
        }
        
        for(int i = 0; i < max_odd.size() - 1 && ones--; i++)
            max_odd[i] = '1';
        return max_odd;
    }
};
