/*
    https://practice.geeksforgeeks.org/problems/form-a-palindrome/0
*/
#include <bits/stdc++.h>
using namespace std;

// Using DP
// TC: O(N^2)
// For each subsequence we find the min no. of insertions
int solve1(string &s) {
    const int N = s.size();
    // dp(i, j): min insertions req in s[i:j]
    vector<vector<int>> dp(N, vector<int>(N, INT_MAX));
    // single char doesnt req any insertion
    for(int i = 0; i < N; i++)
        dp[i][i] = 0;
    
    for(int l = 1; l < N; l++) {
        for(int i = 0; i < N - l; i++) {
            int j = i + l;
            if(i + 1 == j) 
                dp[i][j] = s[i] == s[j] ? 0 : 1;
            else
                dp[i][j] = s[i] == s[j] ? dp[i+1][j-1] :
                            1 + min(dp[i+1][j], dp[i][j-1]);
        }
    }
    
    return dp[0][N-1];
}

// Using DP
// TC: O(N^2)
// Using longest common subsequence:
// Since a palindrome is a seq of chars from front which gets repeated from
// back side of a string as well, so we find the longest common subsequence
// between the original string and its reverse. Finally we need to insert
// N - longest common seq length
int solve2(string &s) {
    const int N = s.size();
    // dp(i, j): len of common subsequence in s[0:i-1] and rev[0:j-1]
    vector<vector<int>> dp(N+1, vector<int>(N+1, 0));
    
    string rev = s;
    reverse(s.begin(), s.end());
    
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++) {
            if(s[i-1] == rev[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], 
                            dp[i][j-1]);
        }
    
    return N - dp[N][N];
}

int main() {
    int t;
    string s;
    cin >> t;
    while(t--) {
        cin >> s;
        //cout << solve1(s) << endl;
        cout << solve2(s) << endl;
    }
	return 0;
}