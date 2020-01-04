/*
    https://leetcode.com/problems/knight-probability-in-chessboard/
    
    Since the knight has 8 valid moves, so total outcomes = 8.
    For each position, find the probability of the knight beging inside the board form
    that position. In the DP cache we store the probability, so everytime when we call for 
    a different state, we get a probability and for getting the total probability for a 
    certain position, sum up all the probabalities of all 8 directions.
    The final answer is chained probability.
    
    TC: O(N * N * K)
    SC: O(N^2)
*/
class Solution {
public:
    double knightProbabilityInside(vector<vector<vector<double> > >& dp,
                                  int N, int K, int i, int j) {
        // base case
        // outside the board
        if(i < 0 || i >= N || j < 0 || j >= N)
            return 0;
        // no moves left and inside the board
        if(K == 0)
            return dp[i][j][K] = 1;
        
        // find the probability of staying inside from this point,
        // this will be chained probability
        if(dp[i][j][K] == 0) {
            dp[i][j][K] += knightProbabilityInside(dp, N, K-1, i - 2 , j + 1)
                            + knightProbabilityInside(dp, N, K-1, i - 2, j - 1)
                            + knightProbabilityInside(dp, N, K-1, i - 1, j - 2)
                            + knightProbabilityInside(dp, N, K-1, i + 1, j - 2)
                            + knightProbabilityInside(dp, N, K-1, i - 1, j + 2)
                            + knightProbabilityInside(dp, N, K-1, i + 1, j + 2)
                            + knightProbabilityInside(dp, N, K-1, i + 2, j - 1)
                            + knightProbabilityInside(dp, N, K-1, i + 2 , j + 1);
            // calculate the probability for the current position 
            dp[i][j][K] /= 8;
        }
        return dp[i][j][K];
    }
    
    
    double knightProbability(int N, int K, int r, int c) {
        // each entry(i, j, k): probability of knight being inside the board from here
        vector<vector<vector<double> > > 
            inside_dp(N, vector<vector<double> >(N, vector<double>(K+1, 0)));
        
        knightProbabilityInside(inside_dp, N, K, r, c);

        return inside_dp[r][c][K];
    }
};
