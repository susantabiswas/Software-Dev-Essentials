/*
    https://leetcode.com/problems/non-overlapping-intervals/
    
    Usually in interval problems, we start with sorting the intervals with
    start position, but in this prob it's better to sort by end position. The reason
    being, we want to ensure we delete min no. of intervals. Now whenever there are two intervals
    overlapping, it's better to delete the one with the bigger end time. This is 
    because the longer end time interval might overlap with more upcoming intervals but the one
    whose end time is shorter will not have the scope of doing that.
    TC: O(nlogn)
    SC: O(n) // sorting
*/
class Solution {
public:
    
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // sort by end position
        sort(intervals.begin(), intervals.end(), 
             [](vector<int>& a, vector<int>& b)->bool { return a[1] < b[1]; });
        int remove = 0;
        
        vector<int> curr = intervals[0];
        for(int i = 1; i < intervals.size(); i++) {
            // Since the second one's end time is greater
            // it must be overlapping. Current interval overlaps, delete the bigger end point one
            // Since all the intervals are sorted by end time, we know that
            // intervals[i] will end later than curr and hence it might get overlapped
            // with many more upcoming intervals, so it's better to delete this instead of
            // previous one, whose end ends before this
            if(curr[1] > intervals[i][0]) {
                ++remove;
            }   
            // end of overlapping intervals, start tracking this interval
            // incase it overlaps with the next one
            else
                curr = intervals[i];
            
        }
        return remove;
    }
};
