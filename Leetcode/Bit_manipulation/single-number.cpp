/*
    https://leetcode.com/problems/single-number/
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int unique = 0;
        // XOR of A XOR A = 0, so all duplicates will cancel each other, 
        // leaving the non duplicate 
        for(int &num: nums)
            unique ^= num;
        return unique;
    }
};
