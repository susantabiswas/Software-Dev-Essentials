/*
    https://leetcode.com/problems/longest-string-chain/
    
    DP Solutions:
    
    Core idea is to save the result: for a given word, how long is the chain 
    length if the word is either at the front or back depending on the way we run the processing.
    
    Below are two ways: 
    1. Adding a new char and going forward in the chain
    2. Removing a char and going back in the chain
    
*/
class Solution {
public:
    // SOLUTION 0: BFS (TLE)
    // TC: O(w) + O((n+1) * 26 * w^2), w = no. of words, n = no. of chars in max length word
    // worst case: When we have w words and they all form a single chain, there will
    // be m + (m - 1) + (m - 2) + .. 1 chains formed
    int bfsSol(vector<string>& w) {
        unordered_set<string> words(w.begin(), w.end());
        int max_len = 0;
        int max_word_len = 0;
        // <word, chain_length>
        queue<pair<string, int> > q;
        
        for(auto word: w) {
            q.push({word, 1});
            max_word_len = max(max_word_len, (int)word.size());
        }
        
        while(!q.empty()) {
            auto [word, len] = q.front();
            q.pop();
            
            max_len = max(max_len, len);
            
            string orig_word(word);
            // for the current word, try inserting chars [a-z] at each possible position
            // and check whether the next word exists in set of words or not
            for(int i = 0; i <= word.size(); i++) {
                auto pos = word.insert(word.begin() + i, 'a');
                for(char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;
                    if(words.count(word)) {
                        q.push({word, len + 1});
                    }
                }
                word = orig_word;
            }
        }
        
        return max_len;
    }
    
    // SOLUTION 1: DP (Style 1)
    // Checking by adding a new char, bigger to smaller words processing
    int dpSol1(vector<string>& words) {
        if(words.empty())
            return 0;
        // <word, max chain length>
        unordered_map<string, int> dp;
        // sort words by word length in descending order
        auto comp = [&](const string& a, const string& b) { return a.size() > b.size(); };
        sort(words.begin(), words.end(), comp);
        int max_len = 1;
        
        for(auto word: words) {
            // Add the initial dp value for the current word i.e 1
            dp[word] = 1;
            
            // add a char at each possible position and check if that exists
            for(int pos = 0; pos <= word.size(); pos++) {
                string new_word(word);
                new_word.insert(new_word.begin() + pos, 'a');
                
                for(char ch='a'; ch <= 'z'; ch++) {
                    new_word[pos] = ch;
                    if(dp.count(new_word)) {
                        dp[word] = max(dp[word], 1 + dp[new_word]);
                        max_len = max(max_len, dp[word]);
                    }
                }
            }
        }
        
        return max_len;
    }
    
    // SOLUTION 2: DP (Style 2)
    // Checking by removing a char, smaller to bigger words processing
    int dpSol2(vector<string>& words) {
        if(words.empty())
            return 0;
        
        // <word, max chain length>
        unordered_map<string, int> dp;
        int max_len = 1;
        
        // sort in ascending order
        auto comp = [&](const string& a, const string& b) { return a.size() < b.size(); };
        sort(words.begin(), words.end(), comp);
        
        for(auto word: words) {
            dp[word] = 1;
            // for the current, try removing char from each position
            for(int pos = 0; pos < word.size(); pos++) {
                string new_word(word);
                new_word.erase(new_word.begin() + pos);
                // check if the new word exists
                if(dp.count(new_word)) {
                    dp[word] = max(dp[word], 1 + dp[new_word]);
                    max_len = max(max_len, dp[word]);
                }
            }
        }
        
        return max_len;
    }
    
    int longestStrChain(vector<string>& words) {
        // TLE solution
        // return bfsSol(words);
        
        // DP solutions
        // return dpSol1(words);
        return dpSol2(words);
        
    }
};
