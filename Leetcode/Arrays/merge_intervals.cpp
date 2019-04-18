/*
    56. Merge Intervals
    https://leetcode.com/problems/merge-intervals/submissions/
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.empty())
            return vector<vector<int> > {};
        
        // sort the intervals by start time
        sort(intervals.begin(), intervals.end());
        
        // whenever the start time of an interval is <= current intervals 
        // end time indicates that the interval can be merged. If the start time
        // is after current intervals end time, that means this interval can't be merged
        // and the interval till now needs to be added to result.
        vector<vector<int> > res;
        int start = intervals.front().front();
        int end = intervals.front().back();
        
        for(int i = 1; i < intervals.size(); i++) {
            // current interval overlaps
            if(intervals[i].front() <= end) {
                // take end time as the max of end times
                end = max(end, intervals[i].back());
            }
            else {
                res.emplace_back(vector<int>{start, end});
                // new start and end times of interval
                start = intervals[i].front();
                end = intervals[i].back();
            }
        }
        
        res.emplace_back(vector<int>{start, end});
        
        return res;
    }
};
