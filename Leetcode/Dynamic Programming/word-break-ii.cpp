/*
    https://leetcode.com/problems/word-break-ii/
    
    TC: O(n * 2^N) [Because of memoization]
    In total 2^N sentences can be there, constructing them takes O(n)
    SC: O(n * 2^N)
    
    There can be 2^N no. of valid sentences, each having n chars.
*/
class Solution {
public:
    vector<string> findSentences(string& s, int start, unordered_set<string>& words,
                                 unordered_map<int, vector<string>>& dp) {
        // Result cached, return the sentences that can be formed from start position
        if(dp.count(start))
            return dp[start];
        
        string substring;
        for(int i = start; i < s.size(); i++) {
            // Instead of calling substring multiple times, we build the substring incrementally
            substring += s[i];
            
            if(words.count(substring)) {
                // Base case: End of string reached
                if(i == s.size() - 1)
                    dp[start].emplace_back(substring);
                else {
                    vector<string> sentences_from_here = findSentences(s, i + 1,
                                                                    words, dp);
                    
                    // Add the current valid word prefix to the result obtained
                    // This will result in a sentence formed out of s[start:N-1]
                    for(auto sentence: sentences_from_here)
                        dp[start].emplace_back(substring + " " + sentence);
                }
            }
        }
        
        return dp[start];
    }
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // make a set of words for faster lookup
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        // dp(i): Sentence that can be formed from ith position i.e in 
        // s[i : N-1] which can be segmented into valid words 
        unordered_map<int, vector<string>> dp;
        
        return findSentences(s, 0, words, dp);
    }
};
