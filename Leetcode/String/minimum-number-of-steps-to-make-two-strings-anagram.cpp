/*
    https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/submissions/
    
    TC: O(N)
    SC: O(26) ~ O(1)
*/
class Solution {
public:
    int minSteps(string s, string t) {
        // find the frequency map of S
        unordered_map<char, int> freq;
        int total = 0;
        
        // frequency map of string S
        for(const char &c: s) {
            freq[c] += 1;
            ++total;
        }
        // Since the only operation is substitution,
        // so finding the no. of chars of S for which there
        // is no counterpart in T is enough, they will be substituted for.
        for(const char &c: t) {
            --freq[c];
            if(freq[c] >= 0)
                --total;
        }
        
        return total;
    }
};
