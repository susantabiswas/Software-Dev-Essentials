/*
    https://leetcode.com/problems/predict-the-winner/
    
    Backtracking Sol:
    TC: O(4^N)
    SC: O(N), Max depth is N
    
    Idea is player 1 will always try to maximize the score, whereas player2 will 
    try to maximize own score and try to minimize the score of player1.
    
    To simulate the behaviour of player 2, we pick the min of the remaining game 
    after player 1 picks a side either front or back
    
    DP Sol:
    TC: O(N^2)
    SC: O(N^2)
    The same sol used for backtracking can be optimized using cache of result for
    each of the function calls. Each call has i and j, so we use cache of size NxN.
    dp[i][j] = score of player1 in range[i:j]
    
    Further Optimization:
    The above way of backtracking involves 4 function calls, this is because we are adding the
    score that player 1 can get and hence accounting the worst available score left by player 2, 
    each time accounting for both when player 2 takes the front and back element.
        Instead of doing this, we can directly put the scores against each, score gained by player 1 = +ve
        and score by player 2 = -ve.
        For given i and j:
            player 1 can take either front and back, this value adds to his/her score. Whatever score player 2 gets
            can be thought of as an opp score. If towards the end, player1's score is still positive then that 
            means player1 has won.
            
    The same flow of can be used for backtracking as well, it will bring down the calls to 2 and TC: O(2^N)
*/
class Solution {
public:
    // Backtracking sol
    long playBacktracking(int start, int end, vector<int>& nums) {
        if(start > end)
            return 0;
        // No matter what player 1 choses, player 2 will try to leave the min available
        // points for player 1 to gather
        int front_chosen = nums[start] + min(playBacktracking(start + 1, end - 1, nums),
                                            playBacktracking(start + 2, end, nums));
        int back_chosen = nums[end] + min(playBacktracking(start, end - 2, nums),
                                         playBacktracking(start + 1, end-1, nums));
        return max(front_chosen, back_chosen);
    }
    
    // DP Memoization solution 1
    // TC: O(N^2)
    // SC: O(N^2)
    long playDPMem1(int start, int end, vector<int>& nums,
                  vector<vector<int>>& dp) {
        if(start > end)
            return 0;
        
        if(dp[start][end] == -1) {
            // No matter what player 1 choses, player 2 will try to leave the min available
            // points for player 1 to gather
            int front_chosen = nums[start] + min(playDPMem1(start + 1, end - 1, nums, dp),
                                                playDPMem1(start + 2, end, nums, dp));
            int back_chosen = nums[end] + min(playDPMem1(start, end - 2, nums, dp),
                                             playDPMem1(start + 1, end-1, nums, dp));
            dp[start][end] = max(front_chosen, back_chosen);
        }
        return dp[start][end];
    }
    
    // DP Memoization solution 2
    // TC: O(N^2)
    // SC: O(N^2)
    long playDPMem2(int start, int end, vector<int>& nums,
                  vector<vector<int>>& dp) {
        if(start > end)
            return 0;
        
        if(dp[start][end] == -1) {
            // Each time the player makes an optimal decision and choses
            // a side that is beneficial, the other player's score for the
            // remaining range is opp and subtracted from curr player's score
            int front_chosen = nums[start] - playDPMem2(start + 1, end, nums, dp);
            int back_chosen = nums[end] - playDPMem2(start, end - 1, nums, dp);
            dp[start][end] = max(front_chosen, back_chosen);
        }
        return dp[start][end];
    }
    
    // Driver for backtracking sol
    bool backTrackingDriver(vector<int>& nums) {
        int player1 = playBacktracking(0, nums.size() - 1, nums);
        int player2 = accumulate(nums.begin(), nums.end(), 0) - player1;
        return player1 >= player2;
    }
    
    // Driver for dp sol 1
    bool dpDriver1(vector<int>& nums) {
        // DP with memoization 1
        // dp[i][j] = max points that player 1 can gather in range[i:j]
        vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), -1));
        int player1 = playDPMem1(0, nums.size()-1, nums, dp);
        int player2 = accumulate(nums.begin(), nums.end(), 0) - player1;
        return player1 >= player2;
    }
    
    // Driver for dp sol 2
    bool dpDriver2(vector<int>& nums) {
        // DP with memoization 1
        // dp[i][j] = net score of player 1 in range[i:j]
        vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), -1));
        return playDPMem2(0, nums.size()-1, nums, dp) >= 0;
    }
    
    bool PredictTheWinner(vector<int>& nums) {
        // Backtracking sol
        // return backTrackingDriver(nums);
        
        // DP with memoization sol 1
        // return dpDriver1(nums);
        
        // DP with memoization sol 2
        return dpDriver2(nums);
    }
};
