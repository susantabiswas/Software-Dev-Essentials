/*
    https://leetcode.com/problems/merge-intervals/
    
    We keep track of current interval and start traversing the array,
    if the interval in array' s start time is more than currently tracked
    interval, we push the currently tracked interval and make the one which was 
    greater as the currently tracked interval.
*/
class Solution {
public:
    // Merges the overlapping intervals
    // TC: O(N), SC: O(N)
    vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
        vector<vector<int>> merged_intervals;
        
        if(intervals.empty())
            return merged_intervals;
        
        // sort the intervals in increasing order acc to start time 
        sort(intervals.begin(), intervals.end());
        
        vector<int> curr_interval = intervals[0];

        for(int i = 1; i < intervals.size(); i++) {
            // if current interval is non-overlapping with
            // the interval at current position, add to intervals array
            if(intervals[i][0] > curr_interval[1]) {
                merged_intervals.emplace_back(curr_interval);
                curr_interval = intervals[i];
            }
            else {
                // current interval overlaps, so update the end time
                curr_interval[1] = max(curr_interval[1], intervals[i][1]);
            }
        }
        // add the last interval
        merged_intervals.emplace_back(curr_interval);
        return merged_intervals;
    }
    
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        return mergeIntervals(intervals);
    }
};
