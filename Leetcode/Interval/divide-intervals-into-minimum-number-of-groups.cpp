/*
    https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/
    
    TC: O(nlogn)
    SC: O(n)
    
    Core idea is that overlapping groups can't be put in the same group. Now how do we
    efficiently whether a given group has interval that overlaps with a given interval or not?
    
    First we make sure that the intervals are processed according to their start point.
    Then we use a height balanced tree to store the end point of each group.
    Since we process intervals by their start and each group has non overlapping intervals,
    we can safely save the end point of last added interval for a given group.
    
    For each interval, we look for the 1st interval whose end is >= start of current interval,
    the current interval can't go to that group but if there is a group before that, then we 
    can put the current interval to that group.
    
    [end < curr_start] [end >= curr_start]
*/
class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        // sort by start point
        sort(intervals.begin(), intervals.end());
        // stores the groups. For each group, we store the end point
        // of last interval in that group
        multiset<int> groups;
        
        for(auto interval: intervals) {
            int start = interval[0], end = interval[1];
            // Find the 1st group whose end point is >= current interval's start
            auto it = groups.lower_bound(start);
            
            // If this is the 1st interval to get a group
            if(groups.empty())
                groups.emplace(end);
            // If there is no group with end point < start
            else if(it == groups.begin()) 
                groups.emplace(end);
            // There is a group with end point < start, we can add
            // the current interval to that group. Update the end
            // point of that group
            else if(*prev(it) < start) {
                groups.erase(prev(it));
                groups.emplace(end);
            }
        }
        return groups.size();
    }
};
