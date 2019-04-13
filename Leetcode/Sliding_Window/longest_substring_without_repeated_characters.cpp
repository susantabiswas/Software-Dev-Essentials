/*
    3. Longest Substring Without Repeating Characters
    https://leetcode.com/problems/longest-substring-without-repeating-characters/
*/


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // when striing is empty
        if(s.empty())
            return 0;
        
        int max_len = 1;
        int i = 0, j = 0;
        bool expand = true;
        
        // for keeping track of unique chars in window
        unordered_set<char> h;
        h.emplace(s[0]);
        
        while(i < s.size()) {
            if(i == j || expand) {
                ++i;
                // string has ended
                if(i == s.size())
                    break;
                // if current char is not unique
                if(h.find(s[i]) != h.end()) {
                    expand = false;
                }
                else {  // when current char is unique 
                    h.emplace(s[i]);
                    
                    // update max length if required
                    max_len = max(max_len, i - j + 1);
                }
            }    
            else {
                // shrink the window till we remove the first instance of repeated char
                // or we have a window of size 1
                while(i != j && s[i] != s[j]) {
                    // remove repeated char
                    h.erase(s[j]);
                    ++j;
                }
                // when j is currently on the first instance of repeated char
                if(i != j) {
                    ++j;
                }
                expand = true;
            }
        }
        
        return max_len;
    }
    
    
    // Solution 2
    int lengthOfLongestSubstring(string s) {
        // marks one position before window start index
        int start = -1;
        // for storing first positions of each char
        vector<int> pos(256, -1);
        int max_len = 0;
        
        for(int i = 0; i < s.size(); i++) {
            // when a character is repeated, its first position will be greater tahn window start
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
};
