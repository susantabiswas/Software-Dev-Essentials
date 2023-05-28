/*
    https://leetcode.com/problems/meeting-rooms/
    
    TC: O(nlogn)
    SC: O(n)
*/
class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        auto comp = [&](const vector<int>& a, const vector<int>& b) {
            return tie(a[0], a[1]) < tie(b[0], b[1]);
        };
        
        sort(intervals.begin(), intervals.end(), comp);
        
        for(int i = 0; i < (int)intervals.size()-1; i++) {
            // when current meeting's end time > next meeting's start time
            // if both current meeting ends at x and next starts at x, then it is possible
            // to attend both.
            if(intervals[i][1] > intervals[i+1][0])
                return false;
        }
        return true;
    }
};
