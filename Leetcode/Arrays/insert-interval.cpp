/*
    https://leetcode.com/problems/insert-interval/submissions/
    
    Idea is to first find the position where the new interval should be inserted and
    it inserts it.
    Then we start merging the overlapping intervals.
    
    TC: O(N), SC: O(N)
*/

class Solution {
public:
    // Merges the overlapping intervals
    // TC: O(N), SC: O(N)
    vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
        vector<vector<int>> merged_intervals;
        
        if(intervals.empty())
            return merged_intervals;
        
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
    
    
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // make sure timings of new interval are sorted
        if(newInterval[0] > newInterval[1]) {
            swap(newInterval[0], newInterval[1]);    
        }

        // find the position where the interval can be placed,
        // then start merging intervals intervals if necessary
        int pos = 0;
        for(int i = 0; i < intervals.size(); i++) {
            // position found to insert
            if(intervals[i][0] > newInterval[0]) {
                break;
            }
            ++pos;
        }
        intervals.insert(intervals.begin() + pos, newInterval);
        
        // merge the overlappig intervals
        vector<vector<int>> merged = mergeIntervals(intervals);
        return merged;
    }
};

////////////////////////////



class Solution {
public:
    // Checks if b overlaps with a or not. 'a' will start first
    // or at the same time
    bool isOverlapping(vector<int>& a, vector<int>& b) {
        return b[0] <= a[1] && b[0] >= a[0];
    }
    
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if(intervals.empty()) 
            return {newInterval};
        if(newInterval.empty()) 
            return intervals;
        
        vector<vector<int>> new_intervals;
        //Find the position where the interval can be inserted
        int pos = 0;
        for(; pos < intervals.size(); pos++) {
            // if current interval can't be put ahead of new interval
            if(intervals[pos][1] >= newInterval[0])
                break;
            new_intervals.emplace_back(intervals[pos]);
        }
        
        // merge any subsequent overlapping intervals
        for(; pos < intervals.size() && 
            (isOverlapping(intervals[pos], newInterval) || isOverlapping(newInterval, intervals[pos])); pos++)
            newInterval = {min(intervals[pos][0], newInterval[0]),
                          max(intervals[pos][1], newInterval[1])};
        
        // insert the new interval
        new_intervals.emplace_back(newInterval);
        
        // add the remaining intervals
        for(; pos < intervals.size(); pos++)
            new_intervals.emplace_back(intervals[pos]);
        
        return new_intervals;
    }
};
