/*
  https://leetcode.com/problems/single-number/
*/

class Solution {
public:
    /// TC: O(N)
    int singleNumber(vector<int>& nums) {
        // Since every number appears twice, XOR of all
        // the numbers will cancel each other except for the 
        // single one
        int ans = 0;
        for(const int& num: nums)
            ans ^= num;
        return ans;
    }
};
