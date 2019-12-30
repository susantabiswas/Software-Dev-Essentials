/*
  https://leetcode.com/problems/perfect-squares/
*/

class Solution {
public:
    // SOLUTION 1
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        
        dp[0] = 0;
        for(int i = 1; i <= n; i++) {
            int j_limit = sqrt(i);
            for(int j = 1; j <= j_limit; j++) {
                dp[i] = min(dp[i], dp[i - j*j] == INT_MAX ? INT_MAX : dp[i - j*j] + 1);
            }
        }
        return dp[n];
    }

    // SOLUTION 2
    // Checks if a number is perfect sq or not
    bool isPerfectSquare(int num) {
        double sq_val = sqrt(num);
        double floor_sq_val = floor(sq_val);

        return sq_val - floor_sq_val == 0;
    }
    
    // driver function
    int numSquares(int n) {
        if(n == 0)
            return 0;

        int n_req = 0;
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        vector<int> perfect_sq;
        
        // find all the numbers that are perfect square in [1:n]
        for(int i = 1; i <= n; i++)
            if(isPerfectSquare(i)) {
                perfect_sq.emplace_back(i);
            }
        
        for(int i = 1; i <= n; i++) {
            // all the numbers in [1:i] that are perfect square
            for(int j = 0; j < perfect_sq.size() && perfect_sq[j] <= i; j++) {
                int req_val = dp[i - perfect_sq[j]] == INT_MAX ? INT_MAX : 1 + dp[i-perfect_sq[j]];
                dp[i] = min(dp[i], req_val);
            }
        }
        return dp[n];
    }
    
};
