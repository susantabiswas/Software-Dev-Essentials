/*
    https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/submissions/
    
    Solution 1: Using bit manipulation
    TC: O(N)
    SC: O(2^k)
    
    // Solution 2: Using string substring
    Idea is to take all windows of size k and put the code in that in a hash table. For k, 2^k codes can be generated.
    So we check we can find that many in the hash table.
    
    TC: O(N)
    SC: O(2^k)
*/
class Solution {
public:
    // SOLUTION 1
    // Using bit manipulation
    bool hasAllCodes(string s, int k) {
        if(s.empty())
            return k == 0;
        // Stores all size k binary codes
        unordered_set<int> bin_codes;
        int num = 0;
        // first window
        for(int i = 0; i < k; i++) {
            num = num * 2;
            num |= s[i] - '0';
        }
        bin_codes.emplace(num);
        for(int i = k; i < s.size(); i++) {
            // remove the first char of previous window and put the current
            // char at last pos
            // If the first char is 1, then only it must have contributed to a number creation
            if(s[i-k] - '0')
                num = num - (1 << k-1);
            num = num*2;
            num |= s[i] - '0';
            bin_codes.emplace(num);
        }
        
        return bin_codes.size() == pow(2, k);
    }
    
    // SOLUTION 2
    // Using substring 
    bool hasAllCodes1(string s, int k) {
        if(s.empty())
            return k == 0;
        // Stores all size k binary codes
        unordered_set<string> bin_codes;
        // first window
        string code = s.substr(0, k);
        bin_codes.emplace(code);
        for(int i = k; i < s.size(); i++) {
            // remove the first char of previous window and put the current
            // char at last pos
            code = code.substr(1) + s[i];
            bin_codes.emplace(code);
        }
        
        return bin_codes.size() == pow(2, k);
    }
};
