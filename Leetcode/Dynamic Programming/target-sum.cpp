/*
    https://leetcode.com/problems/target-sum/
	
	The given sets can be considered as P and N. where N contains the numbers of other set which are
	subtracted.
	P - N = Target(T) ----- 1
    	P + N = S ------------- 2
	Adding (1) and (2)
	=> 2P = T + S
	=> P = (T + S) / 2
	
	=> (T + S) should be even and P = (T + S)/2
  
  Ref:
  https://leetcode.com/problems/target-sum/discuss/97334/Java-(15-ms)-C%2B%2B-(3-ms)-O(ns)-iterative-DP-solution-using-subset-sum-with-explanation
*/

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        // the sum of S and negative set should be even
        if(S > total || (S + total) % 2 != 0)
            return 0;
        
        // If T is negative or either P or N are negative, the essence of 
        // formula stays the same but the positive_set_sum might be negative and
        // throw error, so we take abs of formula
        int positive_set_sum = abs((S + total) / 2);
        
        // each entry i: num of ways in which sum i is possible using the given arrays elements 
        vector<int> dp(positive_set_sum + 1, 0);
        // sum zero is always possible
        dp[0] = 1;
        
        for(const int& num: nums) {
            // starting from back to avoid addition of redundant terms with the 
            // lower values when doing dp[i - num]
            for(int i = positive_set_sum; i >= num; i--) {
                dp[i] += dp[i - num];
            }
        }
        
        return dp[positive_set_sum];
    }
};
