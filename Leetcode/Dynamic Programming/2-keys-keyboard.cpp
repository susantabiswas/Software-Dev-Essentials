/*
    https://leetcode.com/problems/2-keys-keyboard/submissions/
    
    We use the bottom-up approach. For each 'i', find the min steps that will be taken 
    starting with j = 1(A), j = 2(AA) for creating 'i' no. of As.
    Thing to note: State j can be used for creating 'i' iff i is divisible by j, since here we
    have to use only 'j' no. of A each time for creating A, so it should be divisible
*/

class Solution {
public:
    // Optimised solution
    // TC: O(n^2), SC: O(n/2)~O(n)
    int minSteps(int n) {
        if(n == 0 || n == 1)
            return 0;
        // dp[i] indicates the min no. of steps req for making 'i'As.
        // We need to find the computations only till n/2 since after that 
        // nothing can be copied and pasted as a single paste is atleast 2*i and since i > n/2
        // 2*i > n
        vector<int> dp(n/2 + 1, INT_MAX);
        
        dp[0] = dp[1] = 0; 
        for(int i = 2; i <= n/2; i++) {
           for(int j = 1; j < i; j++) {
                // current can't be used for making As if it cannot divide n
                if(i % j == 0) {
                    // (i / j - 1): no. of times to paste
                    // + 1: for copying the pattern
                    dp[i] = min(dp[i], dp[j] + (i / j - 1) + 1);
                }
           }
        }
        
        // we find the min steps out of all the different states
        int ans = INT_MAX;
        for(int j = 1; j <= n/2; j++) {
            // current can't be used for making As if it cannot divide n
            if(n % j == 0) {
                ans = min(ans, dp[j] + (n / j - 1) + 1);
            }
        }
        
        return ans;
    }
    
    // Sol 2
    int minSteps(int n) {
        // dp[i] = Min no. of ops needed to fill i chars
        vector<int> dp(n+1, INT_MAX);
        // no ops needed
        dp[0] = dp[1] = 0;
        
        // For each char 'i', we check all the possible char states 'j' that
        // have appeared so far and check the ops usage if one of those
        // is used for paste operation.
        for(int i = 2; i <= n; i++)
            for(int j = 1; j <= i / 2; j++)
                // if the curr char no. of chars 'j' can make i chars on
                // the screen, then use it (i / j) and add the cost of getting 
                // j chars on screen in the 1st place (dp[j])
                if(i % j == 0)
                    dp[i] = min(dp[i], i / j + dp[j]);
        return dp[n];
    }
};
