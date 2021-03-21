/*
    https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/submissions/
    
    Using sliding window, we try to find the max valid window of atmost K distinct chars.
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int i = 0, j = 0;
        int max_len = 0;
        unordered_map<char, int> freq;
        
        while(i < s.size()) {
            // expand the window till if it is still valid
            if(k >= 0) {
                ++freq[s[i]];
                // new unique char found
                if(freq[s[i]] == 1)
                    --k;
                ++i;
            }
            // make the window valid again
            while(k < 0) {
                --freq[s[j]];
                if(freq[s[j]] == 0)
                    ++k;
                ++j;
            }
            max_len = max(max_len, i - j);
        }
        
        return max_len;
    }
};
