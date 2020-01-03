/*
	https://leetcode.com/problems/out-of-boundary-paths/
*/

class Solution {
private:
    long long MOD = pow(10, 9) + 7;    
public:
    int findPathsRec(vector<vector<vector<int> > >& dp, int m, int n,
                    int N, int i, int j) {
        // base case
        // when out of boundary and N is +ve non-zero
        if(i < 0 || i >= m || j < 0 || j >= n)
            return N >= 0;
        // if N is zero not possible
        if(N <= 0)
            return 0;
        
        if(dp[i][j][N] == -1) {
            dp[i][j][N] = 0;
            // move in 4 directions
            int left = findPathsRec(dp, m, n, N-1, i, j-1);
            int right = findPathsRec(dp, m, n, N-1, i, j+1);
            int top = findPathsRec(dp, m, n, N-1, i-1, j);
            int down = findPathsRec(dp, m, n, N-1, i+1, j);
            
            dp[i][j][N] = (dp[i][j][N] + (left != -1 ? left : 0)) % MOD; 
            dp[i][j][N] = (dp[i][j][N] + (right != -1 ? right : 0)) % MOD;
            dp[i][j][N] = (dp[i][j][N] + (top != -1 ? top : 0)) % MOD;
            dp[i][j][N] = (dp[i][j][N] + (down != -1 ? down : 0)) % MOD;
        }
        return dp[i][j][N] % MOD;
    }
    
    // Driver function for recursive implementation
    int findPathsRecDriver(int m, int n, int N, int i, int j) {
        vector<vector<vector<int> > > dp(m, vector<vector<int> >(n, vector<int>(N+1, -1)));
        return findPathsRec(dp, m, n, N, i, j);
    }
    
    int findPaths(int m, int n, int N, int i, int j) {
        return findPathsRecDriver(m, n, N, i, j);
    }
};
