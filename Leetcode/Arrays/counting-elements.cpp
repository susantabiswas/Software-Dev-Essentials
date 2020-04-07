/*
    https://leetcode.com/explore/featured/card/30-day-leetcoding-challenge/528/week-1/3289/
    
    Given an integer array arr, count element x such that x + 1 is also in arr.

    If there're duplicates in arr, count them seperately.
    Input: arr = [1,1,3,3,5,5,7,7]
    Output: 0
    Explanation: No numbers are counted, cause there's no 2, 4, 6, or 8 in arr.
*/
class Solution {
public:
    int countElements(vector<int>& nums) {
        unordered_set<int> visited;
        
        for(const int& num: nums)
            visited.emplace(num);
        
        int ans = 0;
        for(const int& num: nums) {
            if(visited.find(num + 1) != visited.end())
                ++ans;
        }
        return ans;
    }
};
