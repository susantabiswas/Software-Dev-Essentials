/*
    53. Maximum Subarray
    https://leetcode.com/problems/maximum-subarray/
    
    We keep track of contigous sum till current element. 
    At each index we check if the sum formed till now + current number 
    is the max till current or just the current number is larger. Then update the
    value of global max sum.
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int curr_sum = 0;
        int max_sum = numeric_limits<int> :: min();
        
        // modified Kadane's algo
        for(int i = 0; i < nums.size(); i++) {
            // check the max of current sum including current number
            // or the number alone. This is when there were negative numbers previously 
            // and the current number is greater when added with that sum
            curr_sum = max(curr_sum + nums[i], nums[i]);
            
            max_sum = max(max_sum, curr_sum);
        }
        return max_sum;
    }
};
