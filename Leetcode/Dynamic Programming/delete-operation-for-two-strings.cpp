/*
    https://leetcode.com/problems/delete-operation-for-two-strings/
    
    TC: O(NM)
    SC: O(NM)
    
    Veryu similar to edit distance problem. The change here is that only deletion
    operation is allowed. When we delete a char at pos i from a str, then we compare the next str[i-1]
    char with the other string. So when the two chars are not same, then we pick the deletion
    that gives the min ops overall.
*/
class Solution {
public:
    int tabSol(string& word1, string& word2) {
        const int N = word1.size(), M = word2.size();
        // dp[i][j] = min no. of deletions needed for string A of length i
        // and string B of length j
        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));
        
        // If A is empty, delete all the chars in B
        for(int i = 0; i <= M; i++)
            dp[0][i] = i;
        // If B is empty, delete all the chars in A
        for(int i = 0; i <= N; i++)
            dp[i][0] = i;
        
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= M; j++) {
                if(word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    // either delete a char from A or B
                    dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);
            }
        return dp[N][M];
    }
    
    int minDistance(string word1, string word2) {
        return tabSol(word1, word2);
    }
};
