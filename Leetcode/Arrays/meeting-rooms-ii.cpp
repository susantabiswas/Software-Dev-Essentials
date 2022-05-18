/*
    https://www.lintcode.com/problem/919/

    Get the individual timestamps, sort them in non decreasing order. In case of
    same start and end value, end should comes first as if the meeting ends at T, another
    starts at T, then we need only one room.

    Iterate through the values, for each start time, it means a meeting started and would need
    a room. For each end time, means meeting ended and can vacate the room. Track max rooms used.
    TC: O(nlogn)
    SC: O(n)
*/

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param intervals: an array of meeting time intervals
     * @return: the minimum number of conference rooms required
     */
    int minMeetingRooms(vector<Interval> &intervals) {
        if(intervals.empty())
            return 0;
        
        // Start times are represented as +ve, end times as -ve
        vector<int> timing;

        for(int i = 0; i < intervals.size(); i++) { 
            timing.emplace_back(intervals[i].start);
            timing.emplace_back(-intervals[i].end);
        }

        sort(timing.begin(), timing.end(), [](const int& a, const int& b) -> bool {
            // if both have same timing, then a comes first only if it is end
            if(abs(a) == abs(b) && a != b)
                return a < b;
            return abs(a) < abs(b);
        });
        
        int max_rooms = 0, rooms = 0;

        for(int i = 0; i < timing.size(); i++) {
            rooms += (timing[i] >= 0 ? 1 : -1);
            max_rooms = max(max_rooms, rooms);
        }
            
        return max_rooms;
    }
};
