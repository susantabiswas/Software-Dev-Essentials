/*
    https://leetcode.com/problems/meeting-scheduler/
    
    TC: O((n+m)log(n+m))
    SC: O(n + m)
    n = length of slots1, m = length of slots 2
    
    Idea is to find the intervals that overlap with each other across slots1 and slots2. Once we know an interval overlaps, check the length of common interval and whether it satisfies the duration needed.
*/
class Solution {
public:
    // whether two intervals overlap
    bool isOverlapping(vector<int>& interval1, vector<int>& interval2) {
        return interval1[1] >= interval2[0] || interval2[1] >= interval1[0];
    }
    
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        auto comp = [&](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; };
        // Sort the intervals by their start time
        sort(slots1.begin(), slots1.end(), comp);
        sort(slots2.begin(), slots2.end(), comp);
        
        int i = 0, j = 0;
        int m = slots1.size(), n = slots2.size();
        
        vector<int> common;
        while(i < m && j < n) {
            if(isOverlapping(slots1[i], slots2[j])) {
                // Common interval
                int start = max(slots1[i][0], slots2[j][0]);
                int end = min(slots1[i][1], slots2[j][1]);
                // Check if common duration can meet the meeting demand
                if((end - start) >= duration) {
                    common = {start, start + duration};
                    break;
                }
            }
            // move the interval that ends first
            // When the intervals overlap, move the one that ends first by comparing the end points of both
            if(isOverlapping(slots1[i], slots2[j]) && slots1[i][1] < slots2[j][1])
                ++i;
            else if(isOverlapping(slots1[i], slots2[j]) && slots1[i][1] > slots2[j][1])
                ++j;
            // If non-overlapping, then its is enough to compare the end of one interval with start of another
            else if(slots1[i][1] < slots2[j][0])
                ++i;
            else
                ++j;
        }
        return common;
    }
};
