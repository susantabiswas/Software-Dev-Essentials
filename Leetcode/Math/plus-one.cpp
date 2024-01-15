/*
    https://leetcode.com/problems/plus-one/
    
    TC: O(d), d = no. of digits
    SC: O(1)
    
    Go from right to left and keep adding the carry
*/
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        
        for(int i = digits.size() - 1; i >= 0; i--) {
            digits[i] += carry;
            carry = digits[i] / 10;
            digits[i] %= 10;
        }
        
        if(carry)
            digits.insert(digits.begin(), carry);
        
        return digits;
    }
};
