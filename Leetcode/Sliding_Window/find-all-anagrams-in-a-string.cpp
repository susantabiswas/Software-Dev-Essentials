/*
    https://leetcode.com/problems/find-all-anagrams-in-a-string/submissions/
    
    We use a sliding window for this problem.
    Idea is to keep track of frequency of each window and check if the frequency of chars in the window
    match with that of pattern.
    
    TC: O(N), SC:O(52) ~ O(1)
*/
class Solution {
public:
    // checks if two vectors are same
    // TC: O(26) ~ O(1)
    bool isSame(vector<int>& a, vector<int>& b) {
        for(int i = 0; i < a.size(); i++)
            if(a[i] != b[i])
                return false;
        return true;
    }
    
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        if(s.size() < p.size())
            return result;
        
        const int M = s.size(), N = p.size();
        // frequency of chars in string s and p
        vector<int> s_freq(26, 0), p_freq(26, 0);
        
        // if two strings are anagrams, the frequency of their chars will match 
        // process the first window
        int i = 0;
        for(i = 0; i < N; i++) {
            ++s_freq[s[i] - 'a'];
            ++p_freq[p[i] - 'a'];
        }
        
        // check if the first window is an anagram
        if(isSame(s_freq, p_freq))
            result.emplace_back(i - N);
        // we process the remaining windows and if for any window
        // the char frequencies match, it is an anagram
        for(; i < M; i++) {
            // remove the first char of current window
            --s_freq[s[i - N] - 'a'];
            // add the new char to the current window
            ++s_freq[s[i] - 'a'];
            
            if(isSame(s_freq, p_freq))
                result.emplace_back(i - N + 1);
        }
        return result;
    }
};
