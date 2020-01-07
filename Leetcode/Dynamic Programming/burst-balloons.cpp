/*
  https://leetcode.com/problems/burst-balloons/
*/

class Solution {
public:
    // iterative DP bottom up solution
    int maxCoinsTabular(vector<int>& nums) {
        if(nums.empty())
            return 0;
        
        const int N = nums.size();
        // since nums[-1] = nums[N] = 1, pad the original nums
        nums.insert(nums.begin(), 1), nums.emplace_back(1);
        // dp(i, j): max coins when balloons in [i:j] are burst, we also
        // add 2 more columns to account for -1 and N boundaries
        vector<vector<int> > dp(N + 2, vector<int>(N + 2, 0));
        
        // we approach the balloon bursting from bottom up.
        // for a range [i:j], we find the max coins that we can get in that range
        // if a balloon 'k' is the last one to be burst, i<=k<=j
        // Also since we are thinking in the bottom up way, where the kth balloon is the 
        // last one to be burst, in the original array, we can still have [ : i-1] and [j+1 : ]
        // balloons, so since kth balloon will be the last one in [i:j] range and the corner
        // balloons of [ : i-1] and [j+1 : ] will be on its left and right respectively, so 
        // for bursting it we get nums[i-1] * nums[k] * nums[j+1] + dp[i : k-1] + dp[k+1 : j]
        for(int l = 0; l < N; l++) {
            for(int i = 1; i <= N - l; i++) {
                int j = i + l;
                
                for(int k = i; k <= j; k++) {
                    dp[i][j] = max(dp[i][j], dp[i][k-1] + nums[i-1] * nums[k] * nums[j+1] + dp[k+1][j]);
                }
            }
        }
        return dp[1][N];
    }
    
    int maxCoins(vector<int>& nums) {
        return maxCoinsTabular(nums);
    }
};
