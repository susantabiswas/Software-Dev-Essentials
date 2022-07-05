/*
  https://leetcode.com/problems/student-attendance-record-ii/
*/
class Solution {
int MOD = pow(10, 9) + 7;
public:
    int recMem(int curr, int absent, int late, int n,
              vector<vector<vector<int> > >& dp) {
        if(dp[curr][absent][late] != -1) 
            return dp[curr][absent][late];
        // base case: Max length reached
        if(curr == n) 
            return dp[curr][absent][late] = 1;
        
        if(dp[curr][absent][late] == -1) {
            dp[curr][absent][late] = 0;
            int ending_with_P = 0, ending_with_A = 0, ending_with_L = 0;
            // Status of L will be reset to 0
            ending_with_P = recMem(curr + 1, absent, 0, n, dp) % MOD;
            if(absent == 0)
                ending_with_A = recMem(curr + 1, 1, 0, n, dp) % MOD;
            if(late < 2)
                ending_with_L = recMem(curr + 1, absent, late+1, n, dp) % MOD;

            dp[curr][absent][late] = ((ending_with_P + ending_with_A) % MOD + ending_with_L) % MOD;
        }
        return dp[curr][absent][late] % MOD;
    }

    
    // TC: O(N*A*L) => TLE
    int dpSolDriver1(int n) {
        // There can be atmost 1 absence, 2 Late records
        // In order to save the states, we shave the following values:
        // Absent: [0, 1], Late: [0, 1, 2]
        int max_absent = 1, max_late = 2;
        vector<vector<vector<int> > > dp(n+1, vector<vector<int> >(max_absent + 1, vector<int>(max_late + 1, -1)));
        
        return recMem(0, 0, 0, n, dp);
    }
    
    int dpSolDriver2(int n) {
        // There can be atmost 1 absence, 2 Late records
        // In order to save the states, we shave the following values:
        // Absent: [0, 1], Late: [0, 1, 2]
        int max_absent = 1, max_late = 2;
        vector<vector<vector<int> > > dp(n+1, vector<vector<int> >(max_absent + 1, vector<int>(max_late + 1, -1)));
        
        return recMem(0, 0, 0, n, dp);
    }
    
    int dpTabSol(int n) {
        int MOD = pow(10, 9) + 7;
        // Ways to have rewardable record when we consider only P and L and not A
        
        // dp[i][0] = No. of ways to have a rewardable record which ends with P
        // dp[i][1] = No. of ways to have a rewardable record which ends with L
        // dp[i][2] = No. of ways to have a rewardable record which ends with LL
        vector<vector<long long> > dp(n+1, vector<long long>(3, 0));
        
        // Initial values 
        // Ways of having an empty string is always 1, doesn't matter it is P or L
        dp[0][0] = 1, dp[0][1] = 0;
        // when we have length = 1, We can P or L in exactly one way
        dp[1][0] = dp[1][1] = 1;
        // It is not possible to have a record which ends in LL as it has a size of 2
        // when the record length itself is 0 or 1
        dp[0][2] = dp[1][2] = 0;
        
        for(int l = 2; l <= n; l++) {
            // Ways to have record ending with ..P[l] = P[l-1]P + A[l-1]P + LL[l-2]P
            dp[l][0] = (dp[l-1][0] + dp[l-1][1] + dp[l-1][2]) % MOD;
            // ..L[l] = P[l-1]L, can't have L[l-1]L, as this state should end with a single L
            dp[l][1] = dp[l-1][0];
            // ..LL[l] = P[l-2]LL, can only have a string ending with P before
            dp[l][2] = dp[l-2][0];
        }
        
        long long ways_without_A = (dp[n][0] + dp[n][1] + dp[n][2]) % MOD;
        long long ways_with_A = 0;
        
        // Find the cmb when we put A at the ith position in a record of length n
        for(int i = 0; i < n; i++) {
            long left = (dp[i][0] + dp[i][1] + dp[i][2]) % MOD;
            long right = (dp[n - i - 1][0] + dp[n - i - 1][1] + dp[n - i - 1][2]) % MOD;
            ways_with_A = (ways_with_A + (left * right) % MOD);
        }
        return (ways_without_A + ways_with_A) % MOD;
    }
    
    int checkRecord(int n) {
        // return dpSolDriver1(n);
        return dpTabSol(n);
    }
};
