/*
    https://leetcode.com/problems/palindrome-partitioning/
    
    TC: O(n^2) (for finding palindromic substrings using DP) 
        + O(n * 2^n) (Backtracking, takes O(n) to copy the string to result)
        ~O(n * 2^n)
    SC: O(n), recursive stack

    A simpler way to look at the time complexity:
    For a length n string, for each position, we can choose to either put or not put a partition there.
    e.g "aa", either put/not put a partition at index 0 => "aa", "a","a"
    So 2 * 2 * .. 2 choices (n times)
    With 2 choices and length n, we have 2^n possible partitioned strings.
    
    Also when we create a substring, that substring is actually a part of one of the possible 2^N partitioned strings. So the in total an effort of O(n) will be spent for that full-length partitioned string and hence it takes O(n) for each possible palindromic partition.
    For a total of 2^n strings, we have
    TC: ~O(n * 2^n)
    SC: O(n), recursion depth
*/
class Solution {
public:
    // TC: O(2^N)
    void partitionPalindrome(string& s, int start,
                            vector<vector<bool>>& dp, vector<vector<string> >& result,
                            vector<string> partial) {
        if(start == s.size()) {
            result.emplace_back(partial);
            return;
        }
            
        for(int i = start; i <= s.size(); i++) {
            // if the substring till 'i' is palindromic, recurse for remaining
            if(dp[start][i]) {
                partial.emplace_back(s.substr(start, i - start + 1));
                partitionPalindrome(s, i + 1, dp, result, partial);
                partial.pop_back();
            }
        }
    }
    
    vector<vector<string>> partition(string s) {
        const int N = s.size();
        vector<vector<string> > result;
        vector<string> partial;
        // find all the palindromic substrings and save the the findings
        vector<vector<bool> > dp(N, vector<bool>(N, false));
        
        // all single chars are palindromic
        for(int i = 0; i < N; i++)
            dp[i][i] = true;
        
        for(int l = 1; l < N; l++) {
            for(int i = 0; i < N - l; i++) {    // start index
                int j = i + l;  // end index
                // two chars
                if(i + 1 == j && s[i] == s[j])
                    dp[i][j] = true;
                else 
                    dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1];
            }
        }
        
        // find all the partitions using backtracking
        partitionPalindrome(s, 0, dp, result, partial);
        return result;
    }
};
