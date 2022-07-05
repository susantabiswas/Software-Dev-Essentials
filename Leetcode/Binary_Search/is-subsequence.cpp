/*
    https://leetcode.com/problems/is-subsequence/
    
    Two solutions. 
    2nd sol is suitable for follow-up if m << n:
    for k strings: sol1: O(kn)
                    sol2: O(k * mlogn)
                    
*/

class Solution {
public:
    // TC: O(n + m), n: len(t), m: len(s)
    // SC: O(1)
    // Using two pointers
    bool subsequenceTwoPointers(string& s, string& t) {
        // We use two pointers each starting with the 0th index of 
        // respective strings, then iterate through t and compare the 
        // current chars, after traversal if the ptr for s != len(s),
        // means not all the chars could be covered
        int s_idx = 0;
        for(int t_idx = 0; t_idx < t.size(); t_idx++) {
            if(t[t_idx] == s[s_idx])
                ++s_idx;
        }
        return s_idx == s.size();
    }
    
    // TC: O(mlogn), n: len(t), m: len(s)
    // TC: O(n)
    // Using Binary search
    bool subsequenceBinSearch(string& s, string& t) {
        // Idea is to store the indices in sorted manner for each of the
        // chars of t, then iterate through s and check if that char is present
        // in t using binary search, if it is present at multiple indices, we pick the lowest index
        // to ensure that we pick the substring with lowest ending index for each of the
        // chars, this way we dont miss any sequential char.
        unordered_map<int, vector<int>> char_idx;
        for(int i = 0; i < t.size(); i++) {
            char_idx[t[i]].emplace_back(i);
        }
        // this is the ending index of subsequence of s
        int s_last_idx = 0;
        for(int i = 0; i < s.size(); i++) {
            // current char is not even present
            if(char_idx.count(s[i]) == 0)
                return false;
            // find the lowest index for current char in t
            auto idx = lower_bound(char_idx[s[i]].begin(), char_idx[s[i]].end(), s_last_idx);
            // if no chars could be found
            if(idx == char_idx[s[i]].end())
                return false;
            // update the min position for next char
            s_last_idx = *idx  + 1;
        }
        return true;
    }
    
    bool isSubsequence(string s, string t) {
        //return subsequenceTwoPointers(s, t);
        return subsequenceBinSearch(s, t);
    }
};
