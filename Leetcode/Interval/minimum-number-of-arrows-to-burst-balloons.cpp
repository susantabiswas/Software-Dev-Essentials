/*
    https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
    
    // Idea: Find overlapping intervals such that we stop overlapping
    // when one of the overlapping intervals's end pt is reached
    // 1. if current interval doesnt overlap, burst all the balloons
    // 2. if current interval overlaps, update the limiting endpoint of overlapping interval chain
    
    TC: O(nlogn + n)
    SC: O(n)
*/
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int arrows = 0;
        
        if(points.empty())
            return arrows;
        
        // sort by start pt
        auto comp = [&](const vector<int>& a, const vector<int>& b) { return tie(a) < tie(b); };
        sort(points.begin(), points.end(), comp);
        
        vector<int> curr = points[0];
        
        // Track the current intervals and go through the intervals. We should only launch an arrow when
        // a balloon interval ends (as each balloon needs to burst, we have to shoot)
        for(int i = 1; i < points.size(); i++) {
            // for the currently tracked overlapping balloons, check if the current balloons's
            // interval end is lower than the currently tracked interval. If it is, then burst all the balloons
            // till this point
            curr[1] = min(curr[1], points[i][1]);
            
            if(curr[1] < points[i][0]) { // no overlap, burst the current overlapping balloons
                curr = points[i];
                ++arrows;
            }
        }
        // burst the last balloon
        ++arrows;
        return arrows;
    }
};
