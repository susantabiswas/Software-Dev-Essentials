/*
    https://leetcode.com/problems/word-break-ii/
    
    TC: O(N^2) [Because of memoization]
*/
class Solution {
public:
    bool findSentences(string& s, int start, string partial, 
                       unordered_set<string>& words, unordered_set<string>& result,
                      vector<bool>& dp) {
        
        // all the chars covered
        if(start == s.size()) {
            result.emplace(partial);
            return true;
        }
        // no. of sentences formed before segmentation from current position was done
        int orig_sentences = result.size();
        for(int i = start; i < s.size(); i++) {
            // continue DFS only if valid segmentation is possible from the next char
            if(dp[i+1] == true) {
                string curr_word = s.substr(start, i - start + 1);
                // word found, fix the current word and find the next word
                if(words.find(curr_word) != words.end()) {
                    findSentences(s, i + 1, 
                                  partial + (partial.empty() ? curr_word : " " + curr_word),
                                  words, result, dp);
                }
            }
        }
        // if no sentence could be formed when segmentation started from current start,
        // make the current position as false
        dp[start] = orig_sentences != result.size();
        return dp[start];
    }
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // make a set of words for faster lookup
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        // dp(i): indicates that s[i : N-1] can be segmented into valid words or not 
        vector<bool> dp(s.size() + 1, true);
        unordered_set<string> result;
        string partial;
        
        findSentences(s, 0, partial, words, result, dp);
        return vector<string>{result.begin(), result.end()};
    }
};
