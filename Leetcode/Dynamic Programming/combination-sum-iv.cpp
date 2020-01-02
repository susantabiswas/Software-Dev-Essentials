/*
    https://leetcode.com/problems/combination-sum-iv/
    https://leetcode.com/problems/combination-sum-iv/discuss/468221/C++-solution-explaining-significance-of-loop-order(speed:-100-mem:-100)
*/
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target + 1, 0);
        // zero sum is always possible
        dp[0] = 1;
        
		// finds all permutations
        for(int i = 1; i <= target; i++)
            for(const int& num : nums)
                dp[i] += (i >= num) ? dp[i - num] : 0;
        
        return dp[target];
    }
};
