/*
    https://leetcode.com/problems/amount-of-new-area-painted-each-day/
    
    Idea is to use a height balanced tree to save the intervals. Now for each interval
    we find the position where the interval should lie, then check with its previous if it overlaps.
    If previous overlaps, remove the portion of area common.
    Then start iterating through the intervals that lie after until they overlap. For each overlapping one, subtract
    the common area. We also merge the overlapping intervals. 
    Finally insert the merged interval.
*/
class Solution {
private:
    struct Interval {
        int start, end;
        Interval(int start, int end): start(start), end(end) {};
    };
public:
    // TC: O(nlogn)
    // SC: O(n)
    // Worst case is when we have n disjoint intervals and current intervals overlaps all of them
    // Here it will take O(n) to merge all the intervals, and then insert an interval covering all of them
    // This scenario won't happen often as each time we push an interval covering all the disjoint ones, so the
    // next time even if there is another interval like this, it will see only one interval after it
    vector<int> amountPainted(vector<vector<int>>& paint) {
        vector<int> painted(paint.size(), 0);
        
        // Comparator based on start time
        auto comp = [&](const Interval& a, const Interval& b) { return a.start < b.start; };
        set<Interval, decltype(comp)> intervals(comp);
        
        for(int i = 0; i < paint.size(); i++) {
            Interval interval = {paint[i][0], paint[i][1]};
            
            // find the position where the interval should lie
            auto it = intervals.lower_bound(interval);
            // max possible paintable length
            int length = interval.end - interval.start;
            // tracks the ongoing current interval
            Interval curr = interval;
            
            // check if the previous interval overlaps
            if(!intervals.empty() && it != intervals.begin() && prev(it)->end > interval.start) {
                // common area between the two
                int shared_duration = (min(prev(it)->end, interval.end) - max(prev(it)->start, interval.start));
                length -= shared_duration;
                // merge the intervals
                curr.start = min(curr.start, prev(it)->start);
                curr.end = max(curr.end, prev(it)->end);
                // delete the pervious interval
                intervals.erase(prev(it));
            }
         
            // For all the overlapping intervals, remove the common time duration 
            // they share with the current interval
            while(it != intervals.end() && (interval.end > it->start)) {
                // remove the shared duration
                int shared_duration = (min(it->end, interval.end) - max(it->start, interval.start));
                length -= shared_duration;
                
                // merge the intervals
                curr.start = min(curr.start, it->start);
                curr.end = max(curr.end, it->end);
                ++it;
                intervals.erase(prev(it));
            }
            // insert the merged interval
            intervals.insert(curr);
            
            painted[i] = length;
        }
        return painted;
    }
};
