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


////////////////////////////// SOLUTION 2
/*
    https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/submissions/
    
    452. Minimum Number of Arrows to Burst Balloons
    Medium

    There are some spherical balloons spread in two-dimensional space. For each balloon, provided input is the start and end coordinates of the horizontal diameter. Since it's horizontal, y-coordinates don't matter, and hence the x-coordinates of start and end of the diameter suffice. The start is always smaller than the end.

    An arrow can be shot up exactly vertically from different points along the x-axis. A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend. There is no limit to the number of arrows that can be shot. An arrow once shot keeps traveling up infinitely.

    Given an array points where points[i] = [xstart, xend], return the minimum number of arrows that must be shot to burst all balloons.



    Example 1:

    Input: points = [[10,16],[2,8],[1,6],[7,12]]
    Output: 2
    Explanation: One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).

    Example 2:

    Input: points = [[1,2],[3,4],[5,6],[7,8]]
    Output: 4

    Example 3:

    Input: points = [[1,2],[2,3],[3,4],[4,5]]
    Output: 2

    Example 4:

    Input: points = [[1,2]]
    Output: 1

    Example 5:

    Input: points = [[2,3],[2,3]]
    Output: 1

    Constraints:

    0 <= points.length <= 104
    points[i].length == 2
    -231 <= xstart < xend <= 231 - 1

    All the balloons need to bursted, so in worst case
    we can use N arrows and burst all. To optimize arrows
    we need to shoot at points with max number of intersecting
    balloons, but finding that makes the problem look very difficult.
    If we observe carefully and look at this sentence "All the balloons need to be burst",
    we can find a clue, since each balloon needs to burst anyway, we can shoot at its end point 
    and allow any balloons which also gets covered also be bursted. If we chose a point before the 
    end point then we might have missed a balloon intersection towards the end. 
    One important thing is to start wrt to the end pt and not start pt, that way we will
    know the extent till which a particular balloon can cover.
    
    TC: O(nlogn)
    SC: O(n)
*/
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.empty()) 
            return 0;
        
        // sort wrt the end point
        sort(points.begin(), points.end(),
            [](auto &a, auto &b) -> bool {
                return a[1] < b[1]; 
            });
        
        int burst_pt = points[0][1], arrows = 1;
        for(auto &point: points) {
            if(point[0] > burst_pt)
                ++arrows, burst_pt = point[1];
        }
        return arrows;
    }
};
