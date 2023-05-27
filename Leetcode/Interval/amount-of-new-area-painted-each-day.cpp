/*
    https://leetcode.com/problems/amount-of-new-area-painted-each-day/
    
    Solution 1: Height Balanced Tree
    
    Idea is to use a height balanced tree to save the intervals. Now for each interval
    we find the position where the interval should lie, then check with its previous if it overlaps.
    If previous overlaps, remove the portion of area common.
    Then start iterating through the intervals that lie after until they overlap. For each overlapping one, subtract
    the common area. We also merge the overlapping intervals. 
    Finally insert the merged interval.
    
    
    Solution 2: Sweep Line
    Imagine a 2D coordinate system. We have 2 kinds of event points: Start interval and End interval points.
    We create a point(index, event_type) and plot on the grid. Now imagine there is a vertical line going from left to
    right. for a given x coordinate, it will process all the points there. So Start interval events will result in the 
    points being added and End interval points will result in the points being removed from the sweep line.
    
    In each event point, we save the {day_supposed_to_be_painted, whether_start} information.
    Now the idea is for a given interval point (x coordinate), the smallest index day out of all the current days in the sweep line
    will actually paint that.
    So we pick the smallest day index from the sweep line and for that day index do += 1, indicating that for that day a point was painted.
    
    1------2, day=0
    1--------------4, day=1
    
    Points = [[], [(0, T), (1, T)], [(0, F)], [], [(1, F)]]
    Sweep Line:
    x=0, line = {}
    x=1, line={0, 1} => coord x=1 should be painted on day 0
    x=2, line={1} => coord x=2 should be painted on day 1, day0 event point end received so removed from line 
    x=3, line={1} => coord x=3 should be painted on day 1
    x=4, line={} => coord x=4 not painted as it is an exit point for day1 
    
    Work done = [1, 2]
*/
class Solution {
private:
    struct Interval {
        int start, end;
        Interval(int start, int end): start(start), end(end) {};
    };
    
    struct Point {
        int day; // Day on which this point is supposed to be painted
        bool is_start;
        
        Point(int day, bool is_start): day(day), is_start(is_start) {};
    };
public:
    ///////////////////////////////////// SOLTUION 1
    // TC: O(nlogn)
    // SC: O(n)
    // Worst case is when we have n disjoint intervals and current intervals overlaps all of them
    // Here it will take O(n) to merge all the intervals, and then insert an interval covering all of them
    // This scenario won't happen often as each time we push an interval covering all the disjoint ones, so the
    // next time even if there is another interval like this, it will see only one interval after it
    vector<int> treeSol(vector<vector<int>>& paint) {
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
                --it;
                curr.start = min(curr.start, it->start);
            }
         
            // For all the overlapping intervals, remove the common time duration 
            // they share with the current interval
            while(it != intervals.end() && (interval.end > it->start)) {
                // remove the shared duration
                int shared_duration = (min(it->end, interval.end) - max(it->start, interval.start));
                length -= shared_duration;
                
                // merge the intervals
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
    
    /////////////////////////////////////////// SOLUTION 2
    // TC: O(nlogn + m), n = no. of points, m = farthest point
    // SC: O(n)
    vector<int> sweepLineSol(vector<vector<int>>& paint) {
        vector<int> painted(paint.size(), 0);
        // Find the farthest right point
        auto comp = [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; };
        int farthest_pt = (*max_element(paint.begin(), paint.end(), comp))[1];
        
        // Add the pts to the coordinate system
        // points[x] = [Point] Point events for given x coordinate
        // For each of the interval coordinates, we store the info about the day
        // on which it is supposed to be painted
        // Eg points[1] = [Point(0, true), Point(2, true)]
        // Above means that for interval starting with 1, it should be painted
        // on days 0 and 2.
        vector<vector<Point> > points(farthest_pt + 1);
        for(int day = 0; day < paint.size(); day++) {
            points[paint[day][0]].emplace_back(Point(day, true)); // entry point
            points[paint[day][1]].emplace_back(Point(day, false)); // exit point
        }
        // This is an imaginary vertical line that will traverse from left to right
        // Stores the vertical points for a given x coordinate
        set<int> sweep_line;
        
        for(int x = 0; x <= farthest_pt; x++) {
            // Add all the event points for given x
            for(auto point: points[x]) {
                if(point.is_start)
                    sweep_line.emplace(point.day);
                else
                    sweep_line.erase(point.day);
            }
            // For the current x coordinate, pick the smallest day index
            // when the pt will be painted
            if(!sweep_line.empty())
                painted[*sweep_line.begin()] += 1;
        }
        return painted;
    }
    
    vector<int> amountPainted(vector<vector<int>>& paint) {
        // return treeSol(paint);
        return sweepLineSol(paint);
    }
};
