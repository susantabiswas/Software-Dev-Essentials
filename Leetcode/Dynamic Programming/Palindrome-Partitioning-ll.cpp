// https://www.codingninjas.com/studio/problems/873266
// Palindrome Partitioning ll 
// TC: O(n^2)
// SC: O(n^2)

int mem(int i, int j, vector<vector<bool>>& dp,
    vector<vector<int>>& parts) {
//cout<<"$"<<i<<" "<<j<<" "<<dp[i][j]<<endl;
        // base case: when s[i:j] is a plaindrome
        if(i == j || dp[i][j])
            return parts[i][j] = 0;

        if(parts[i][j] == INT_MAX) {
            // make a partition for each position
            for(int k = i; k <= j-1; k++) {
                parts[i][j] = min(parts[i][j], 
                    1 + mem(i, k, dp, parts) + mem(k+1, j, dp, parts));
            }
        }

        return parts[i][j];
}

int palindromePartitioning(string str)
{
   int n = str.size();
   vector<vector<bool>> dp(n, vector<bool>(n, false));

   for(int i = 0; i < n; i++)
        dp[i][i] = true;

    for(int l = 1; l < n; l++)
        for(int start = 0; start < n - l; start++) {
            int end = start + l;

            if(start == end - 1)
                dp[start][end] = (str[start] == str[end]);
            else {
                dp[start][end] = (str[start] == str[end]) && dp[start+1][end-1];
            }
        }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++)
    //         cout << dp[i][j]<<" ";
    //     cout<<endl;
    // }
        
    vector<vector<int>> parts(n, vector<int>(n, INT_MAX));
    mem(0, n-1, dp, parts);

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++)
    //         cout << parts[i][j]<<" ";
    //     cout<<endl;
    // }

    return parts[0][n-1];
}
