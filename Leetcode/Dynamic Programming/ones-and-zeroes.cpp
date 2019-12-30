/*
    https://leetcode.com/problems/ones-and-zeroes/
*/
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
    
        // each entry: no. of strings that can be formed with m and n
        vector<vector<int> > dp(m+1, vector<int>(n+1, 0));
        
        /*
            This is a knapsack problem with 'm' and 'n' that can be considered weights.
            So just like the classical problem can be solved with 1D array, for m and n
            we use 2D matrix.
            
            For each entry: check if current string can be formed 
                            + no. of strings that can be formed with remaining n and m
                            
            For doing this if we start from top and go towards bottom(smallest value of n and m to largest), 
            then we end up counting reduntant things. Eg: m = 10, n = 10 will also capture the string that
            m = 1, n = 1 can. So if the current string is such that it can be captured by last m and n values and
            the current m and n can also cover it, then when we do dp[i - zeros][j - ones], it will give us 1 for the same 
            thing again.
            So we iterate through the strings, and for the current string we start filling m X n matrix from bottom right
            to top left. So since upper values can be filled only when the lower values are filled so this time when
            1 +  dp[i - zeros][j - ones] is done, dp[i - zeros][j - ones] will only account for the values till the 
            string before the current string.
            for ith string, dp[i][j] has info about the ith string and dp[i-1][j-1] has info till i-1th string, 
            so adding it won't create any redundancy.
        */
        
        for(const string& str: strs) {
            // calculate the no. of ones and zeros required
            int zeros = count(str.begin(), str.end(), '0');
            int ones = str.size() - zeros;
            
            for(int i = m; i >= 0; i--) {
                for(int j = n; j >= 0; j--) {
                    // current can be considered iff we have required no. of ones and zeros
                    int including_current = (zeros <= i && ones <= j) ? 1 + dp[i - zeros][j - ones] : 0;
                    dp[i][j] = max(dp[i][j], including_current);
                }
            }    
        }
        return dp[m][n];
    }
};
