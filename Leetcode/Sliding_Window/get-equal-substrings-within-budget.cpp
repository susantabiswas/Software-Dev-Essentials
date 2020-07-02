/*
    https://leetcode.com/problems/get-equal-substrings-within-budget/
    
    We use a sliding window of max length such that the chars inside can be all same.
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int i = 0, j = 0, max_len = 0, cost = 0;
        const int N = s.size();
        
        while(i < N) {
            // expand the window
            if(cost <= maxCost) {
                cost += s[i] != t[i] ? abs(s[i] - t[i]) : 0;
                ++i;
            }
            // check if the string has become invalid or not
            while(cost > maxCost) {
                cost -= s[j] != t[j] ? abs(s[j] - t[j]) : 0;
                ++j;
            }
            // update the length iif req
            max_len = max(max_len, i - j);
        }
        
        return max_len;
    }
};
