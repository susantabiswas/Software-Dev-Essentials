/*
    https://leetcode.com/problems/number-of-longest-increasing-subsequence/
    
    The idea is for each index 'i', we find the longest subarray length
    ending there and also the no. of subarray of such length ending there.
    We do this for all the idices starting from 1 to N-1.
    
    TC: O(N^2)
    SC: O(N)
*/
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if(nums.size() <= 1)
            return nums.size();
        // pair: first: length of longest increasing subarray ending here
        //       second: no. of subarrays with this subarray length
        vector<pair<int, int>> dp(nums.size(), make_pair(1,1));
        int result = 0;
        // length of maximum subarray
        int max_len = 0;
        
        for(int i = 1; i < nums.size(); i++)
            for(int j = 0; j < i; j++) {
                // the LIS will be updated iff the subarry ending at 'j'th index
                // has a longer subarray and that element is greater than ith element
                if(nums[j] < nums[i] && dp[j].first + 1 >= dp[i].first) {
                    // if the jth element has the same max subarray length
                    // we increment the counter of no. of such subarrays for current 'i'
                    if(dp[j].first + 1 == dp[i].first) {
                        dp[i].second += dp[j].second;
                    }
                    else {
                        // if the jth LIS is greater, then update the ith LIS and
                        // also the counter for the no. of such subarrays
                        dp[i].first = dp[j].first + 1;
                        dp[i].second = dp[j].second;
                    }
                }
                // update max length subarray
               if(max_len < dp[i].first)
                   max_len = dp[i].first;
            }
        
        // find all the LIS which are of max length
        // and add their count of max subarray LIS
        for(const auto& lis: dp)
            if(lis.first == max_len)
                result += lis.second;
                
        return result;
    }
};
