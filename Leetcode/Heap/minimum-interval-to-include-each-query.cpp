/*
    https://leetcode.com/problems/minimum-interval-to-include-each-query/
    
    Solution 1: Sweep Line
    TC: O((n + q)log(n + q) + nlogn), Sorting + (insert/delete in set)
    SC: O(n + q), n = no. of intervals, q = no. of queries
    
    The coordinates of both the intervals and queries can be thought of as events. We
    add some additional info with each event.
    Event = <point, index, point_type>
    
    Then sort the events by position, we start processing the events from left to right. Imagine
    these points on a graph and a vertical line (sweep line) processing these from left to right. 
    The processing for an event depends on the type of event. For an interval whose start point has
    been processed, it is added to a set where we save it's gap. When we get it's end point, we remove the corresponding 
    gap from set. When the event is a query type, we pick the smallest gap from the set.
    
    Solution 2: Heap
    TC: O(nlogn (sorting intervals) + nlogn (sorting queries) + nlogn (heap insert/delete))
    SC: O(n)
    
    Idea is to sort both the intervals and queries by position. Now iterate from the smallest to biggest query, for each query
    start iterating from the sorted intervals and put the ones which start before query pt, these are our candidates.
    We use a min heap where the key is the gap of the interval. Next remove the intervals out of candidates which have
    end pt < query pt. Now if there is any interval in heap, that is the ans for the given query.
*/
class Solution {
public:
    // Solution 1: Line Sweep
    vector<int> lineSweepSol(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> result(queries.size(), -1);
        
        // Event types: Ordered priority wise, when it comes to processing
        enum { Start, Query, End } PointType;
        
        // Add all the events
        // There are 3 type of events: 
        // 1. Start: Interval start point 
        // 2. End: Interval end point
        // 3. Query: point of query
        
        // <point, index, point_type>
        vector<array<int, 3>> events;
        // add the interval points as events, start and end points are separate events
        for(int i = 0; i < intervals.size(); i++) {
            events.push_back({intervals[i][0], i, Start});
            events.push_back({intervals[i][1], i, End});
        }
        
        // add the query points as events
        for(int i = 0; i < queries.size(); i++)
            events.push_back({queries[i], i, Query});
        
        // sort the events by position and then based on priority of processing
        auto comp = [&](const array<int, 3>& a, const array<int, 3>& b) { 
            // query type event comes later
            if(a[0] == b[0])
                return a[2] < b[2];
            return a[0] < b[0]; 
        };
        sort(events.begin(), events.end(), comp);
        
        // Tracks the events in the current sweep
        // We track the interval gap of the interval type event in
        // a set so that we can get the smallest gap efficiently
        multiset<int> sweep_line;
        
        for(int i = 0; i < events.size(); i++) {
            // Add and process the event
            int idx = events[i][1];
            
            // Interval type event
            if(events[i][2] == Start) {
                // This is start point of interval, save the gap of this interval 
                // as part of sweep
                int gap = intervals[idx][1] - intervals[idx][0] + 1;
                sweep_line.emplace(gap);
            }
            // Interval type event
            else if(events[i][2] == End) {
                // this is end point of an interval
                // remove the interval gap from line sweep
                int gap = intervals[idx][1] - intervals[idx][0] + 1;
                auto it = sweep_line.lower_bound(gap);
                sweep_line.erase(it);
            }
            // Query type event
            else {
                // Since we already have intervals added as part of current sweep, so all the points
                // in the current line sweep are eligible for the query, pick the one with the smallest gap
                int gap = sweep_line.begin() == sweep_line.end() ? -1 : *sweep_line.begin();
                int idx = events[i][1];
                result[idx] = gap;
            }
        }
        
        return result;
    }
    
    
    // Solution 2: Heap
    vector<int> heapSol(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> result(queries.size());
        
        // <pt, index in orig array>
        vector<pair<int, int> > query_idx(queries.size());
        for(int i = 0; i < queries.size(); i++)
            query_idx[i] = make_pair(queries[i], i);
            
        // sort the interval and queries by position
        // sort by start
        sort(intervals.begin(), intervals.end());
        sort(query_idx.begin(), query_idx.end());
        
        // <gap, interval idx>
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > min_heap;
        // tracks index of intervals array
        int idx = 0;
        for(auto [query_pt, q]: query_idx) {
            // add the candidate intervals, whose start <= query pt
            for(; idx < intervals.size() && intervals[idx][0] <= query_pt; idx++) 
                min_heap.push({intervals[idx][1] - intervals[idx][0] + 1, idx});
            
            // remove the intervals whose end pt < query pt
            while(!min_heap.empty() && intervals[min_heap.top().second][1] < query_pt) 
                min_heap.pop();
            
            result[q] = min_heap.empty() ? -1 : min_heap.top().first;
        }
        return result;
    }
    
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        // return lineSweepSol(intervals, queries);
        return heapSol(intervals, queries);
    }
};
