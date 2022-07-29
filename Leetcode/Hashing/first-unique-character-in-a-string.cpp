/*
    https://leetcode.com/problems/first-unique-character-in-a-string/
    
    TC: O(N), N: length of string
    SC: O(M), M: unique chars
*/

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> idx;
        
        for(int i = 0; i < s.size(); i++)
            ++idx[s[i]];
        // Non repeating char will have count of 1
        for(int i = 0; i < s.size(); i++)
            if(idx[s[i]] == 1)
                return i;
        return -1;
    }
};

//////////////////////////
class Solution {
public:
    int firstUniqChar(string s) {
        int idx = INT_MAX;
        unordered_map<char, int> pos;
        
        // find the position of each char in string,
        // incase a char was already seen, we dont update
        // its position value but make it negative to indicate
        // that the char was already seen
        for(int i = 0; i < s.size(); i++) {
            // first seeing the char, save its 1-based index
            if(pos.count(s[i]) == 0)
                pos[s[i]] = i+1;
            // char appearing again, so make it negative
            else if(pos[s[i]] > 0)
                pos[s[i]] *= -1;
        }
        
        // find the smallest index of unique number
        for(auto it = pos.begin(); it != pos.end(); it++) {
            // if the char is unique, then its index will be +ve
            if(it->second > 0)
                idx = min(idx, it->second);
        }
        return idx == INT_MAX ? -1 : idx-1;
    }
};
