/*
    https://leetcode.com/problems/my-calendar-i/
    
    TC: O(logn) for each book() call
    
    To find the position where to insert an interval, it takes O(logn) using binary search
    on a sorted set of intervals. For storing the intervals in sorted manner, we use a height balanced 
    tree and then on that we can do a search for an interval in O(logn).
    
    book(interval):
        0. If no intervals exist, just add
        1. Check if the interval should exist at front or back
        2. If it lies in between intervals, check
        [prev_start, prev_end) <= [start, end) <= [next_start, next_end)
*/
class MyCalendar {
private:
    struct Interval {
        int start = -1;
        int end = -1;
        Interval(int start, int end): start(start), end(end) {};
    };
    
    struct IntervalComp {
        bool operator()(const Interval& a, const Interval& b) const {
            return a.start < b.start;
        }
    };
    
    set<Interval, IntervalComp> intervals;
public:
    MyCalendar() {
        
    }
    
    // TC: O(logn)
    // SC: O(height = logn)
    bool book(int start, int end) {
        Interval interval(start, end);
        // When there are no intervals
        if(intervals.empty()) {
            intervals.emplace(interval);
            return true;
        }
        
        // If the interval lie at either of the extreme ends i.e front or back
        // Interval should lie at the front
        if(intervals.begin()->start >= end) {
            intervals.emplace(interval);
            return true;
        }
        // Interval should lie at the back
        else if(prev(intervals.end())->end <= start) {
            intervals.emplace(interval);
            return true;
        }
        
        // Interval should lie between two existing intervals.
        // Find the position of the interval whose start time is >= current interval's start
        // using Binary search
        auto pos = intervals.lower_bound(interval);
        
        // Interval with next greater start found, check 
        // [prev_start, prev_end) <= [start, end) <= [next_start, next_end)
        if(prev(pos)->end <= start && pos->start >= end) {
            intervals.emplace(interval);
            return true;
        }
        return false;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
