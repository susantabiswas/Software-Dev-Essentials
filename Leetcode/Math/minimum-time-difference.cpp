/*
    https://leetcode.com/problems/minimum-time-difference/
    
    TC: O(nlogn)
    SC: O(n)
    
    For each two timestamps t1 and t2 (t1 < t2), we can compute the difference in two ways:
    1. t1 --> t2 (clockwise)
    2. t2 <-- t1 (anti-clockwise)
    
    Eg t1 = 00:00, t2 = 23:59, clockwise: 23:59 and anti-clockwise: 00:01
    We sort all the timestamps and compute the diff for each of the pairs.
    Thing to note is we don't need to compute in both the ways for intermediate timestamps
    T[i] and T[i+1] because T[0] and T[N-1] are smallest and biggest respectively and hence
    would have chance of having the smallest anti-clockwise time diff.
*/
class Solution {
public:
    // Time diff (mins) Anti-clockwise between t1 and t2, t2<---t1 (t2 > t1)
    int antiClockwiseTime(int h1, int m1, int h2, int m2) {
        return (h1 * 60 + m1) + ((24 - h2 - 1) * 60 + (60 - m2));
    }
    
    // Clockwise diff (mins) between t1 and t2, t1--->t2 (t2 > t1)
    int clockwiseTime(int h1, int m1, int h2, int m2) {
        return (h2 * 60 + m2) - (h1 * 60 + m1);
    }
    
    // Extracts hours and minutes from string timestamp
    pair<int, int> extractHoursMins(string timestamp) {
        int hrs = stoi(timestamp.substr(0, 2));
        int mins = stoi(timestamp.substr(3, 2));
        return {hrs, mins};
    }
    
    int findMinDifference(vector<string>& timePoints) {
        // sort the timestamps
        sort(timePoints.begin(), timePoints.end());
        int N = timePoints.size();
        int min_diff = INT_MAX;
        
        // Between two timestamps t1 and t2 (t2 > t1), there can be two ways to compute the time difference.
        // 1. Time diff between t2 --> t1
        // 2. Time diff between t2 --> t1
        // Since we have sorted the timestamps, we don't need to compute time diff both clockwise and anticlockwise
        // for all i and i+1 pairs. We can do both only for the 1st and last timestamps and for the rest, we can just do 
        // clockwise (t1 --> t2) for all the other pairs.
        for(int i = 0; i < N - 1; i++) {
            auto [h1, m1] = extractHoursMins(timePoints[i]);
            auto [h2, m2] = extractHoursMins(timePoints[i + 1]);
            
            min_diff = min(min_diff, clockwiseTime(h1, m1, h2, m2));
        }
        
        // 1st element is the smallest and last is the biggest in [0, 23:59] scale, so 
        // also compare between 1st and last
        auto [h1, m1] = extractHoursMins(timePoints[0]);
        auto [h2, m2] = extractHoursMins(timePoints[N-1]);
        
        int curr_min_diff = min(clockwiseTime(h1, m1, h2, m2), 
                                antiClockwiseTime(h1, m1, h2, m2));
        min_diff = min(min_diff, curr_min_diff);

        return min_diff;
    }
};
