/*
    https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/submissions/
    
    Using sliding window, we try to find the max valid window of atmost K distinct chars.
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    /////////////////// SOLUTION 1
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int max_len = 0, n = s.size();
        int start = 0, end = 0;
        unordered_map<char, int> freq;
        
        while(end < n) {
            // expand the window
            ++freq[s[end++]];
            // If the state is unsafe, make it safe again by shrinking the window
            while(freq.size() > k) {
                char ch = s[start++];
                if(--freq[ch] == 0) 
                    freq.erase(ch);
            }
            // update the maximum length
            max_len = max(max_len, end - start);
        }
        return max_len;
    }
    
    ////////////////// SOLUTION 2
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
