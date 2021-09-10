/*
    https://leetcode.com/problems/shifting-letters/submissions/
*/
class Solution {
public:
    // TC: O(N)
    // SC: O(1)
    string shiftingLetters(string s, vector<int>& shifts) {
        int accumulated_shifts = 0;
        
        // For ith position, all the chars from 0th index to ith index
        // are shifted, which means the total shifts  for ith char =
        // sum of total shifts in N - i positions in shifts array, since
        // all the chars from ith till N-1th position will be contributing to ith position also
        for(int i = s.size() - 1; i >= 0; i--) {
            // Circle around to prevent overflow
            accumulated_shifts += shifts[i] % 26;
            accumulated_shifts %= 26;
            s[i] = (char)('a' + (accumulated_shifts + (s[i] - 'a')) % 26);
        }
        
        return s;
    }
    
    /*
    // TC: O(N)
    // SC: O(N)
    string shiftingLetters(string s, vector<int>& shifts) {
        vector<int> total_shifts(s.size(), 0);
        int accumulated_shifts = 0;
        
        // For ith position, all the chars from 0th index to ith index
        // are shifted, which means the total shifts  for ith char =
        // sum of total shifts in N - i positions in shifts array, since
        // all the chars from ith position will be contributing to ith position also
        for(int i = s.size() - 1; i >= 0; i--) {
            // Circle around to prevent overflow
            accumulated_shifts += shifts[i] % 26;
            accumulated_shifts %= 26;
            total_shifts[i] = accumulated_shifts;
        }
        
        // Shift the chars
        for(int i = 0; i < s.size(); i++)
            s[i] = (char)('a' + (total_shifts[i] + (s[i] - 'a')) % 26);
        return s;
    }
    */
};
