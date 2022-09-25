/*
    https://leetcode.com/problems/sort-the-people/
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        // <height, index>
        unordered_map<int, int> idx;
        // save the indices for each of the heights
        for(int i = 0; i < heights.size(); i++)
            idx[heights[i]] = i;
        
        // sort in descending order
        sort(heights.begin(), heights.end(), greater<>());
        vector<string> result;
        
        // Now based on the sorted heights, we put the names
        for(int i = 0; i < heights.size(); i++) {
            result.emplace_back(names[idx[heights[i]]]);
        }
        
        return result;
    }
};
