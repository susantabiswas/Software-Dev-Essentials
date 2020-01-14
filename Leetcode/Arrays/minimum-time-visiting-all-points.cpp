/*
    https://leetcode.com/problems/minimum-time-visiting-all-points/
    
    Everytime find the distance between the x and y coordinates of next point from current position.
    Now since only horizontal, vertical and diagonal movement is allowed, we should try to cover max possible
    distance in min time, that can be done by moving diagonally. This diagonal distance will make us
    reach the min(x2, y2), then we travel the distance gap between (x2, y2).
    
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int total_time = 0;
        for(int i = 1; i < points.size(); i++) {
            int x_dist = abs(points[i][0] - points[i-1][0]);
            int y_dist = abs(points[i][1] - points[i-1][1]);
            
            total_time += x_dist > y_dist ? x_dist : y_dist;
        }
        return total_time;
    }
};
