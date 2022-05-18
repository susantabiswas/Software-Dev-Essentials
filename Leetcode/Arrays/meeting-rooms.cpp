/*
    https://www.lintcode.com/problem/920/

    Just check if there is any overlap between any of the intervals.__asm__
    TC: O(NlogN)
    SC: O(N)
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
     * @return: if a person could attend all meetings
     */
    bool canAttendMeetings(vector<Interval> &intervals) {
        if(intervals.empty())
            return true;
        // Sort by start time
        auto comp = [&](const Interval& a, const Interval& b) { return a.start <= b.start; };
        sort(intervals.begin(), intervals.end(), comp);

        // Find if there is any overlap between the meetings
        for(int i = 1; i < intervals.size(); i++) {
            if(intervals[i-1].end > intervals[i].start)
                return false;
        }
        return true;
    }
};
