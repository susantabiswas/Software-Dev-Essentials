/*
    https://leetcode.com/problems/isomorphic-strings/
    
    Use two hash tables, one is used to keep track of the mapping between the chars and
    another to track which chars have got a mapping.
    Then for each unequal chars, check if there exists a matching mapping otherwise check if a mapping can be made.
    TC: O(n)
    SC: O(m), m = no. of unique chars
*/
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size() != t.size())
            return false;
        
        // <char in s, char in t>
        unordered_map<char, char> replacement;
        // Tracks all the chars in t for which there is a mapping
        unordered_set<char> taken;
        
        for(int i = 0; i < s.size(); i++) {
            // if there is a replacement for the curr char, check if it matches
            if(replacement.count(s[i])) {
                // check if the replacement match
                if(replacement[s[i]] != t[i])
                    return false;
            }
            // no replacement for the curr char, set the replacement char equal to t[i]
            // if that char is already taken, then not isomorphic since strings won't  be equal anymore
            else {
                // if char is already taken
                if(taken.count(t[i]))
                    return false;
                replacement[s[i]] = t[i];
                taken.emplace(t[i]);
            }
        }
        return true;
    }
};
