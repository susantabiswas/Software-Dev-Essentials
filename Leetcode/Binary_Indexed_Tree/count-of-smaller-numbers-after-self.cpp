/*
    https://leetcode.com/problems/count-of-smaller-numbers-after-self/
    
    TC: O(n * log(offset)), n = size of nums
    SC: O(offset)
    
    Since we want to know the no. of smaller elements than x on the right, we use a counter/bucket
    array for possible values. For the nums seen, we update the buckets based on the frequency.
    
    For a num x, we need to find sum of element's frequencies in [-INF, x-1] range.
    This is nothing but range sum, so we can use segment tree or BIT to efficiently query the ranges.
    
    The BIT stores the frequency sum from [-INF, x].
    
    Since we cant access negative index in array, we add a positive offset to make the lowest negative 
    positive. 
    NOTE: Everything in BIT is 1 indexed, usually 0 is often not needed and is used directly as dummy node.
    Here though 0 is a possible value hence it can also have value, so 0 also needs to shift to make sure that
    0th position is still empty and hence we need to add +1 to each index explicitly to make them shift to right by 1 position.
*/
class Solution {
    int offset = 1e4;
    // Range of values: [-offset:offset]
    // Since we want 1 based indexing, we add an extra 1
    // we have offset no. of numbers on left and right side of 0 and 0 itself as a candidate number
    int n = (2 * offset + 1) + 1; 
    vector<int> bit;
public:
    
    void update(int idx, int delta) {
        while(idx < bit.size()) {
            bit[idx] += delta;
            idx = idx + (idx & -idx);
        }
    }
    
    int query(int idx) {
        int range_sum = 0;
        
        while(idx > 0) {
            range_sum += bit[idx];
            idx = idx - (idx & -idx);
        }
        return range_sum;
    }
    
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> result(nums.size());
        bit.resize(n, 0);
        
        // Since we have to find the smaller number on right side,
        // So start creating the BIT from right side and the current number
        // is only updated once it is done processing. This makes sure that the smaller
        // numbers on left are not seen and only the ones on right are seen.
        for(int idx = nums.size()-1; idx >= 0; idx--) {
            // Offset added to shift negative numbers to positive side
            // +1 because we have 0 also as a number and hence to keep the 
            // 1st node as dummy we have to shift everything to right by 1
            int shifted_num = nums[idx] + offset + 1;
            // Range sum in [-offset + offset : nums[idx] + offset]
            result[idx] = query(shifted_num - 1);
            // Update the count for nums[idx]
            update(shifted_num, 1);
        }
        
        return result;
    }
};
