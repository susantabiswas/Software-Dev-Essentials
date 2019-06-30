/*
    https://leetcode.com/problems/edit-distance/submissions/
*/

class Solution {
public:
    // Top down solution
    int editDistanceRec(string& w1, string& w2, int n, int m, vector<vector<int>>& dp) {
        // insert chars equal to remaining word2 length
        if(n == 0)
            return dp[n][m] = m;
        // delete chars equal to remaining word1 length
        if(m == 0)
            return dp[n][m] = n;
        
        if(dp[n][m] == 0) {
            // when both chars are same, no need for any operation
            if(w1[n-1] == w2[m-1])
                dp[n][m] = editDistanceRec(w1, w2, n-1, m-1, dp);
            else // when chars are diff, select the min cost operation
                dp[n][m] = 1 + min({editDistanceRec(w1, w2, n, m-1, dp),    // insert
                            editDistanceRec(w1, w2, n-1, m, dp),    // delete 
                            editDistanceRec(w1, w2, n-1, m-1, dp)   // substitute
                            });
        }
            
        return dp[n][m];
    }
    
    int editDistanceTabular(string& word1, string& word2, vector<vector<int>>& dp) {
        const int N = word1.size();
        const int M = word2.size();
        
        // when there are no chars from word1
        for(int j = 0; j <= M; j++)
            dp[0][j] = j;
        
        // when there are no chars from word2
        for(int i = 0; i <= N; i++)
            dp[i][0] = i;
        
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                /// when chars are same
                if(word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else {
                    dp[i][j] = 1 + min({dp[i-1][j-1],
                                       dp[i-1][j],
                                       dp[i][j-1]});
                }
            }
        }
        
       return dp[N][M];
    }
    
    int minDistance(string word1, string word2) {
        // cache for dp
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        
        int ans = editDistanceTabular(word1, word2, dp);
        //int ans = editDistanceRec(word1, word2, word1.size(), word2.size(), dp);
        return ans;
    }
};
