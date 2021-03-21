/*
    https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/
    
    Using sliding window, we try to find the max valid window of atmost 2 distinct chars.
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int i = 0, j = 0;
        int max_len = 0;
        unordered_map<char, int> freq;
        
        while(i < s.size()) {
            // expand window if cond still holds
            if(freq.size() <= 2) {
                ++freq[s[i]];
                ++i;
            }
            // make the window valid again
            while(freq.size() > 2) {
                --freq[s[j]];
                if(freq[s[j]] == 0)
                    freq.erase(s[j]);
                ++j;
            }
            
            max_len = max(max_len, i - j);
        }
        return max_len;
    }
};
