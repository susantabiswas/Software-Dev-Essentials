/*
    https://leetcode.com/problems/find-the-highest-altitude/
    
    TC: O(n)
    SC: O(1)
*/
class Solution {
public:
    int largestAltitude(vector<int>& gains) {
        // We start from height = 0
        int max_height = 0;
        int height = 0;
        
        // keep updating the height by adding the gain of current
        // position compared to previous
        for(auto gain: gains) {
            height += gain;
            max_height = max(max_height, height);
        }
        return max_height;
    }
};
