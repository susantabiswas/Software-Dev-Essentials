/*
    https://leetcode.com/problems/data-stream-as-disjoint-intervals/
    
    Two Approaches:
    1. Here we use a height balanced tree to store the data as numbers. 
    addNum() is log(n). When we want to get the intervals, we do the merging and this takes O(n)
    
    2. Here we use an array such that there are intervals present and already they are disjoint.
    For each addNumber() it takes O(n) to merge any overlapping intervals.
    For get intervals, it takes O(1) since the intervals are already maintained.
*/
//////////////////////////////////// SOLUTION 1
class SummaryRanges {
private:
    set<int> nums;
public:
    SummaryRanges() {
        
    }
    
    // TC: O(logn)
    void addNum(int val) {
        nums.emplace(val);
    }
    
    // TC: O(n)
    vector<vector<int>> getIntervals() {
        vector<vector<int>> intervals;
        // current ongoing interval
        vector<int> interval;
        
        for(auto it = nums.begin(); it != nums.end(); it++) {
            // Start of the 1st interval
            if(interval.empty())
                interval = {*it, *it};
            // If current number belongs to the ongoing interval i.e
            // it's consecutive to last number
            else if(interval[1] == *it - 1)
                interval[1] = *it;
            // If current number is not part of ongoing interval
            // Add the ongoing interval and set the new interval with 
            // current number
            else {
                intervals.emplace_back(interval);
                interval = {*it, *it};
            }
        }
        // Add the last ongoing interval
        intervals.emplace_back(interval);
        return intervals;
    }
};

/*
////////////////////////////////////// SOLUTION 2
class SummaryRanges {
private:
    vector<vector<int>> intervals;
public:
    SummaryRanges() {
        
    }
    
    // TC: O(n)
    void addNum(int val) {
        int start = val, end = val;
        
        // Find the position where the [val, val] interval should fall,
        // then merge the overlapping intervals
        auto comp = [&](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; };
        auto it = lower_bound(intervals.begin(), intervals.end(), vector<int>{start, end}, comp);
        
        // no interval after this, but the previous interval overlaps
        if(it != intervals.begin() && prev(it)->back() + 1 >= start) 
            --it;
        // merge the overlapping intervals
        while(it != intervals.end() && end + 1 >= it->front()) {
            start = min(start, it->front());
            end = max(end, it->back());
            
            // remove the current interval. when erasing with iterator, iterator points the next element
            intervals.erase(it);
        }
        intervals.insert(it, {start, end});
    }
    
    // TC: O(1)
    vector<vector<int>> getIntervals() {
        return intervals;
    }
};
*/
/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
