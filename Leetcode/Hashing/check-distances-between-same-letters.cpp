/*
    https://leetcode.com/problems/check-distances-between-same-letters/
    
    TC: O(n)
    SC: O(26)
    
    Store the 1st position of each char and then when the next instance of that
    char is seen, check if the distance is equal to distance[char].
*/
class Solution {
public:
    bool checkDistances(string s, vector<int>& distance) {
        unordered_map<char, int> pos;
        
        for(int idx = 0; idx < s.size(); idx++) {
            char ch = s[idx];
            // seeing for the 1st time
            if(pos.count(ch) == 0)
                pos[ch] = idx;
            else {
                int dist = idx - pos[ch] - 1;
                if(dist != distance[ch - 'a'])
                    return false;
            }
        }
        return true;
    }
};
