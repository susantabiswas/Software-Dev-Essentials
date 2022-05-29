/*
    https://leetcode.com/problems/partition-array-for-maximum-sum/
    
    Core idea is for a given starting index, we try creating partitions of size
    1 to k and recurse the same for the remaining elements. 
    [start: start + partition_size -1] + max sum of remaining nums[start + partition_size: N-1]
*/
class Solution {
public:
    // Top-Down solution
    // TC: O(Nk)
    // SC: O(N)
    int memSol(int start, int k, 
               vector<int>& nums, vector<int>& dp) {
        // base case
        if(start == nums.size())
            return 0;
        
        if(dp[start] != -1) {
            // Max element in the current parition_size window, i.e max in nums[start: start + partition_size -1]
            int max_el = INT_MIN;
            for(int partition_size = 1; partition_size <= k && (start + partition_size - 1) < nums.size(); partition_size++) {
                max_el = max(max_el, nums[start + partition_size - 1]);
                // check if current partition [start: start + partition_size -1] + max sum of remaining nums[start + partition_size: N-1]
                dp[start] = max(dp[start],
                                    (partition_size * max_el) + memSol(start + partition_size, k, nums, dp)); 
            }
        }   
        return dp[start];
    }
    
    // Bottom-up solution
    // TC: O(Nk)
    // SC: O(N)
    int tabSol(vector<int>& nums, int k, vector<int>& dp) {
        // since we are doing bottom-up and need result of max sum of remaining nums[start + partition_size: N-1]
        // we start from back, so that we can have the result of remaining elements ready 
        for(int start = dp.size()-1; start >= 0; start--) {
            int max_el = INT_MIN;
            for(int partition_size = 1; partition_size <= k && (start + partition_size - 1) < nums.size(); partition_size++) {
                // Max element in the current parition_size window, i.e max in nums[start: start + partition_size -1]
                max_el = max(max_el, nums[start + partition_size - 1]);
                // check if current partition [start: start + partition_size -1] + max sum of remaining nums[start + partition_size: N-1]
                dp[start] = max(dp[start],
                               max_el * partition_size 
                                + ((start + partition_size) >= nums.size() ? 0 : dp[start + partition_size]));
            }        
        }   
        return dp[0];
    }
    
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        // dp[i] = max sum value starting ith index with partitioning
        vector<int> dp(arr.size(), -1);
        // return memSol(0, k, arr, dp);
        return tabSol(arr, k, dp);
    }
};
