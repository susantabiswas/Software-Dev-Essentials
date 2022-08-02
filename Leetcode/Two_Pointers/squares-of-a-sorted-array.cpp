/*
    https://leetcode.com/problems/squares-of-a-sorted-array/
    
    All the numbers are in ascending order, but
    final output is sq of each, so negative numbers can
    mess up the order. Since negative numbers will occupy the
    front of array if they exists, we use two pointers to compare 
    and decide which number is bigger and put it in the final sorted order.
    
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        // Init with 0, since the smallest negative number will give the largest sq 
        // This pointer will point to pos number in case neg numbers are not there 
        int neg_idx = 0;
        // Largest pos number
        int pos_idx = nums.size() - 1;
        
        vector<int> sorted(nums.size());
        for(int i = sorted.size() - 1; i >= 0; i--) {
            // compare & pick the larger sq
            int num1 = nums[neg_idx] * nums[neg_idx];
            int num2 = nums[pos_idx] * nums[pos_idx];
            
            sorted[i] = num1 > num2 ? num1 : num2;
            
            if(num1 > num2) 
                ++neg_idx;
            else
                --pos_idx;
        }
        
        return sorted;
    }
};
