/*
    https://leetcode.com/problems/employee-free-time/
    
    TC: O(nlogn), n = total no. of intervals
    SC: O(n)
    
    We will only know about the gap intervals when we look at all the intervals in a single view. So to do so, we take all the intervals from all the workers and merge the overlapping intervals. Once we have non overlapping intervals, we can find the gaps between consecutive intervals.
    
*/
/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        
        vector<Interval> intervals;
        // Add all the intervals from all the workers
        for(auto worker: schedule)
            for(auto interval: worker)
                intervals.emplace_back(interval);
        
        vector<Interval> merged_intervals;
        vector<Interval> interval_gaps;
        
        // Sort the intervals by start time and merge the overlapping intervals
        sort(intervals.begin(), intervals.end(), 
             [](const Interval &a, const Interval& b) -> bool {
                return a.start < b.start; 
             });
        
        Interval curr = intervals[0];
        
        for(int i = 1; i < intervals.size(); i++) {
            // if the current interval overlaps with ongoing interval
            if(curr.end >= intervals[i].start)
                curr.end = max(curr.end, intervals[i].end);
            // ongoing interval doesn't overlap with current interval
            else {
                // check if the last interval and current interval has a gap or not
                if(curr.end < intervals[i].start) 
                    interval_gaps.emplace_back(Interval{curr.end, intervals[i].start});
                
                // Interval is disjoint, insert the ongoing interval and set 
                // ongoing interval to current interval
                merged_intervals.emplace_back(curr);
                curr = intervals[i];
            }
        }
        return interval_gaps;
    }
};
