/*
    https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
    
    TC: O(nlogn + max(10k, nlogn))
    sorting + max(10k iterations, there can be max of n insertions/deletions)
    ~ O(max(10k, nlogn))
    
    SC: O(n)
    
    Looking at this problem, first thing that comes to the mind are patterns similar to other
    interval problems.
    But this problem actually uses a different pattern.
    
    Identification: When there are intervals and we want to process events at some points like
        here it is each day.
        Similar problem is https://leetcode.com/problems/minimum-interval-to-include-each-query/
        Here the query points are the events where we process something.
        
    Idea:
        - All the intervals are our candidates for processing.
        - We use a heap (min/max) to keep track of ongoing events.
        - At each processing event:
                1. Remove all the invalid intervals, like for this problem it is the intervals that have already passed.
                2. Then add the valid intervals, here it is the intervals that starts on that day
                3. Now after above two steps, our heap will have potential candidates that are valid, we pick element(s) based on the problem.
                    In this problem it is basically getting the interval whose end day is the nearest.
*/

class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        // sort the events by start day
        sort(events.begin(), events.end());
        
        int attend = 0;
        // This saves the end day of events
        priority_queue<int, vector<int>, greater<int>> min_heap;
        int i = 0;
        
        for(int day = 1; day <= 100000; day++) {
            // Stage 1: Candidate Elimination
            // remove all the events which have already ended before today
            while(!min_heap.empty() && min_heap.top() < day)
                min_heap.pop();
            
            // Stage 2: Add candidates
            // Here add all the events that start on current day
            while(i < events.size() && events[i][0] == day)
                min_heap.push(events[i++][1]);
            
            // Pick the event with closest end day
            if(!min_heap.empty()) {
                ++attend;
                min_heap.pop();
            }
        }
        
        return attend;
    }
};
