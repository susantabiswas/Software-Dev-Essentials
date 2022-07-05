/*
    https://leetcode.com/problems/employee-free-time/
    
    SOLUTION 1
    TC: O(nlogn), n = total no. of intervals
    SC: O(n)
    
    We will only know about the gap intervals when we look at all the intervals in a single view. So to do so, we take all the intervals from all the workers and merge the overlapping intervals. Once we have non overlapping intervals, we can find the gaps between consecutive intervals.
    
    SOLUTION 2
    TC: O(nlogk), n = total no. of intervals, k = no. of workers
    SC: O(k)
    
    Same overall logic as above, just that we use the fact that the individual arrays are sorted. So to sort the
    overall intervals we use that fact. This is similar to merge k sorted array.
    We use a heap to sort the intervals in O(nlogk), and use the same logic as above to find the disjoint gaps.
    Brief about merge k sorted problem:
    Use a min heap, where we start with the 1st element of each array. Each time we pop the element with the smallest
    start time, then check if there is one element after that in that array. If there is a next element, then add the
    next element to heap.
    
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
    // SOLUTION 1: SORTING
    // TC: O(nlogn)
    vector<Interval> sol1(vector<vector<Interval>>& schedule) {
        vector<Interval> intervals;
        // Add all the intervals from all the workers
        for(auto worker: schedule)
            for(auto interval: worker)
                intervals.emplace_back(interval);
        
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
                curr = intervals[i];
            }
        }
        return interval_gaps;
    }
    
    // SOLUTION 1: HEAP
    // TC: O(nlogk)
    struct VectorIterator {
        bool operator>(const VectorIterator& other) const {
            return curr->start > other.curr->start;
        }
        // Start and End iterator ptr 
        vector<Interval>::const_iterator curr, last;    
    };
    
    vector<Interval> sol2(vector<vector<Interval>>& schedule) {
        auto comp = [&](const VectorIterator& a, const VectorIterator& b) { return a.curr->start > b.curr->start; };
        priority_queue<VectorIterator, vector<VectorIterator >, decltype(comp)> min_heap(comp); 
        
        // Add the 1st interval of each worker
        for(int i = 0; i < schedule.size(); i++)
            min_heap.emplace(VectorIterator{schedule[i].cbegin(), schedule[i].cend()});
        
        vector<Interval> gap_intervals;
        Interval curr = {-1, -1};
        
        while(!min_heap.empty()) {
            auto it = min_heap.top();
            min_heap.pop();
           
            // If ongoing interval is uninitialized, set to curr interval to it
            // Just initialized curr interval, so need to proceed with the rest of the 
            // flow since that would be comparing with itself
            if(curr.start == -1 && curr.end == -1) {
                curr = *(it.curr);
                // Add the next interval of this worker's schedule
                if(it.curr != it.last)
                    min_heap.emplace(VectorIterator{it.curr, it.last});
                continue;
            }
            
            // update the ongoing interval's end time if it overlaps
            if(curr.end >= it.curr->start)
                curr.end = max(curr.end, it.curr->end);
            // curr interval is non-overlapping with ongoing interval
            else {
                // if there is gap between the ongoing interval and next interval
                if(curr.end < it.curr->start) 
                    gap_intervals.emplace_back(Interval{curr.end, it.curr->start});
                curr = *(it.curr);
            }
            // Add the next interval of this worker's schedule
            ++it.curr;
            if(it.curr != it.last)
                min_heap.emplace(VectorIterator{it.curr, it.last});
            
        }
        return gap_intervals;
    }
    
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        // return sol1(schedule);
        return sol2(schedule);
    }
};
