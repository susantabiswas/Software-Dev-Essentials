/*
    https://leetcode.com/problems/subarray-sum-equals-k/
    TC: O(N^2), SC: O(N)
    
    
    // Solution 1
    We track the cummulative sum and use a hash table [sum, value].
    Idea is that if we are getting the same sum at different indices, that
    means the inner sum from previous index till current is 0, sum[i] = x,
    sum[j] = x + 0, inner sum being 0 makes the cummulative sum 0 again.
    
    Similarly if we get sum[j] = sum[i] + k, means the inner sum was k and that is what 
    we want to find out.
    
    // Solution 2
    Idea is to save the cummulative sum of array, since we want to find the
    contiguous sum, that can be used. 
    
    for getting sum of subarray of A[i:j] = sum[0:j] - sum[0:i-1] 
*/
class Solution {
public:
    // Solution 1
    // TC: O(N), SC:O(N)
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> cumm_sum;
        
        int k_sum = 0;
        int total_sum = 0;
        
        // cummulative sum before the first element
        cumm_sum[0] = 1;
        
        for(int i = 0; i < nums.size(); i++) {
            total_sum += nums[i];
            // check if total_sum - k has been seen before or not
            if(cumm_sum.count(total_sum - k)) {
                // add all occurrences of subarrays ending with (total-k) sum
                // before current index
                k_sum += cumm_sum[total_sum - k];
            }
            // put the current sum if not present
            // since any subarray found later that has only current total_sum +k
            // can make subarray with all previous subarrays ending with that sum
            if(cumm_sum.count(total_sum) == 0)
                cumm_sum[total_sum] = 1;
            else
                cumm_sum[total_sum] += 1;
        }
        return k_sum;
    }
    
    // Solution 2
    // TC: O(N^2), SC: O(N)
    int subarraySum2(vector<int>& nums, int k) {
        // find the cummmulative sum
        vector<int> cumm_sum(nums.size(), 0);
        
        for(int i = 0; i < nums.size(); i++)
            cumm_sum[i] = nums[i] + (i-1 >= 0 ? cumm_sum[i-1] : 0);
        
        int k_sum = 0;
        // find the sum of all the subarrays
        for(int i = 0; i < nums.size(); i++) {
            for(int j = i; j < nums.size(); j++) {
                int subarray_sum = i > 0 ? cumm_sum[j] - cumm_sum[i-1] : cumm_sum[j];
                if(subarray_sum == k)
                    ++k_sum;
            }
        }
        
        return k_sum;
    }
};
