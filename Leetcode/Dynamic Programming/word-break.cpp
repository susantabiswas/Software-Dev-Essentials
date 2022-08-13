/*
    https://leetcode.com/problems/word-break/
    
    TC: O(N^3)
    SC: O(n)
    
    Idea is to use backtracking + DP. In normal backtracking we would have
    start from current position and iterated till n-1 and made substrings in between.
    If a substring is a valid word, we recurse from the next position of that word and go on.
    
    Thing is, we might reach the same position multiple times and again do computation from there,
    wasting compute. Instead we use a dp cache that saves whether it is possible to segment the string
    from a given position or not. Before starting the next recursion call, check the cache value to decide
    whether to recurse or not.
*/
class Solution {
public:
    // TC: O(N^3), For each call, we iterate through all n positions and
    // also we create a string that can again take O(n) in worst case.
    // In worst case we make n calls, iterate n times in each call and make substrings.
    bool segment(int curr, string& s, unordered_set<string>& words,
                vector<bool>& dp) {
        // base case: end of string
        if(curr == s.size())
            return true;
        
        for(int i = curr; i < s.size(); i++) {
            // check if the substring is a valid word or not
            // and if it is safe to recurse further
            string word = s.substr(curr, i - curr + 1);
            if(words.count(word) && dp[i+1] && segment(i+1, s, words, dp)) 
                return true;
        }
        // Since we have reached this point, means we were not able to find a segment
        // the string into valid words from this point onwards
        return dp[curr] = false;
    }
    
    bool wordBreak(string s, vector<string>& wordDict) {
        // dp[i] = Whether it is possible to segment the string from ith position till n-1
        vector<bool> dp(s.size(), true);
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        
        return segment(0, s, words, dp);
    }
};
