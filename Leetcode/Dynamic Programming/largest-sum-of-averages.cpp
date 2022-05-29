/*
    https://leetcode.com/problems/largest-sum-of-averages/
    
    It is easier to get the feel of the sol using recursive sol.
    Core idea is given k max partitions and A[i:j], we need to
    do paritioning at each possible position k times. 
    We precompute the cummulative sum so that avg computation becomes faster.
    
    - given 'k'
    - given range i and j
    for pos from i to j-k:
        partition the array in two parts: avg(A[i:pos]) + (Max avg for range A[pos+1:j] and k=K-1)
    Pick the max avg score parition cmb from previous step for range i to j 
*/
class Solution {
public:
    // Finds the avg for a given range of numbers
    double avg(int start, int end, vector<long>& cumm_sum) {
        // special care when start = 0, in that case sum is basically from 0 to end
        return (double)(cumm_sum[end] - (start > 0 ? cumm_sum[start-1] : 0)) / (end - start + 1);
    }
    
    // Sol1: Using Memoization
    // TC: O(NK)
    // SC: O (NK)
    double memSol(int start, int end, int k, vector<int>& nums,
              vector<long>& cumm_sum, vector<vector<double>>& dp) {
        // base case: only 1 partition i.e entire array
        if(k == 1)
            return avg(start, end, cumm_sum);
        
        if(dp[start][k] == -1) {
            // Partition the array at all possible positions and pick the 
            // cmb that works the best
            for(int pos = start; pos <= end - k + 1; pos++) 
                dp[start][k] = max(dp[start][k],
                                  avg(start, pos, cumm_sum) + memSol(pos+1, end, k-1, nums, cumm_sum, dp));
        }
        return dp[start][k];
    }
    
    // Sol 2: Bottom-up Tabular approach
    // TC: O(NK)
    // SC: O(NK)
    double tabSol(int K, vector<int>& nums, 
                  vector<long>& cumm_sum, vector<vector<double>>& dp) {
        const int N = nums.size();
        
        // base case, when only 1 partition is there
        // avg of entire elements of array
        for(int i = 0; i < N; i++)
            dp[i][1] = avg(i, N-1, cumm_sum);
        
        for(int k = 2; k <= K; k++) 
            for(int start = 0; start <= N-k; start++) {
                // select each position and partition the
                // nums in 2 primary groups, one on left nums[start: pos]
                // which is a single parition and since the smaller subproblems
                // are solved pick the best cmb of remaining elements on right dp[pos+1][k-1]
                for(int pos = start; pos <= N-k; pos++) {
                    dp[start][k] = max(dp[start][k],
                                      avg(start, pos, cumm_sum) + dp[pos+1][k-1]);
                }
            }
        return dp[0][K];
    }
    
    double largestSumOfAverages(vector<int>& nums, int k) {
        const int N = nums.size();
        // dp[i][k] = Max avg score from nums[0] to nums[N-1] 
        // when k partitions are allowed 
        vector<vector<double>> dp(N, vector<double>(k+1, -1));
        // cumm_sum[i] : Cummulative sum from 0 to ith element
        vector<long> cumm_sum(N, 0);
        for(int i = 0; i < N; i++)
            cumm_sum[i] += nums[i] + (i > 0 ? cumm_sum[i-1] : 0);
        
        // return memSol(0, N-1, k, nums, cumm_sum, dp);
        return tabSol(k, nums, cumm_sum, dp);
    }
};
