/*
    https://leetcode.com/problems/jewels-and-stones/
    
    Use a hash table to track the jewels. Traverse the stones
    we have and check for each if they are a jewel or not.
    
    TC: O(S + J), SC: O(J), S: no. of stones, J: no. of jewels
*/

class Solution {
public:
    // TC: O(S), SC: O(J)
    int numJewelsInStones(string J, string S) {
        // Hash table of all the jewels
        unordered_set<char> jewels(J.begin(), J.end());
        int jewel_stones = 0;
        
        for(const char& c: S)
            // if current stone is a jewel stone
            if(jewels.count(c))
                ++jewel_stones;
        
        return jewel_stones;
    }
};
