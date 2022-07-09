/*
    https://leetcode.com/problems/positions-of-large-groups/
*/
class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s) {
        vector<vector<int>> groups;
        int n = s.size();
        
        for(int i = 0; i < n; ) {
            int j = i + 1;
            while(j < n && s[j] == s[j-1])
                ++j;
            int group_len = j - i;
            
            if(group_len >= 3)
                groups.emplace_back(vector<int>{i, j-1});
            i = j;
        }
        return groups;
    }
};
