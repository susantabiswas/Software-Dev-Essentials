/*
    https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // marks one position before window start index
        int start = -1;
        // for storing first positions of each char
        vector<int> pos(128, -1);
        int max_len = 0;
        
        for(int i = 0; i < s.size(); i++) {
            // when a character is repeated, its first position will be greater than window start
            // so we take the start position at its first occurrence
            if(pos[s[i]] > start) {
                start = pos[s[i]];
            }
            // update first occurrence position of current char, since its first occurrence is 
            // now one position before current window start
            pos[s[i]] = i;
            // update max len if required
            max_len = max(max_len, i - start);
        }
        
        return max_len;
    }
    
    // TC: O(N)
    // Using Sliding window
    int lengthOfLongestSubstring(string s) {
        int i = 0, j = 0;
        // for storing first positions of each char
        vector<int> dict(256, 0);
        int max_len = 0;
        bool repeating = false;
        
        while(i < s.size()) {
            ++dict[s[i]];
            if(dict[s[i]] > 1)
                repeating = true;
            ++i;
           
            while(repeating) {
                --dict[s[j]];
                if(dict[s[j]] >= 1)
                    repeating = false;
                ++j;
            }
            
            max_len = max(max_len, i - j);
        }
        
        return max_len;
    }
};
