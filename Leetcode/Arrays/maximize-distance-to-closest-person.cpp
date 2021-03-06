/*
    https://leetcode.com/problems/maximize-distance-to-closest-person/submissions/
    
    // Solution 1
    Idea is to find the closest distance of an occupied seat  on left and right side. Now the
    max separation for any seat will be minimum of left and right side values. We pick the max 
    separation by doing this for all the seats.
    TC: O(N)
    SC: O(N)
    
    Solution 2
    Idea is find the max gap between two 1s with 0s in between.
    TC: O(N)
    SC: O(1)
*/

class Solution {
public:
    // Solution 2
    int maxDistToClosest(vector<int>& seats) {
        int occupied = -1, max_dist = 0;
        
        for(int i = 0; i < seats.size(); i++) {
            // if the current seat if occupied
            if(seats[i]) {
                // leftmost seat is vacant
                if(occupied == -1)    
                    max_dist = max(max_dist, i);
                // we have found an interval with vacant seats in between
                else 
                    max_dist = max(max_dist, (i - occupied) / 2);
                occupied = i;
            }
        }
        // now if the rightmost is vacant, check
        int N =  seats.size();
        if(seats[N-1] == 0)
            max_dist = max(max_dist, N - occupied - 1);
        return max_dist;
    }
    
    // Solution 1
    int maxDistToClosest1(vector<int>& seats) {
        // Distance from the closest left occupied seat
        unordered_map<int, int> left_dist;
        int occupied = INT_MAX;
        int max_dist = 0;
        // find the distance of each vacant seat from its closest left occupied seat
        for(int i = 0; i < seats.size(); i++) {
            if(seats[i] == 1)
                occupied = i;
            else
                left_dist[i] = occupied == INT_MAX ? INT_MAX : i - occupied;
        }
        
        // Now start checking from right side, the distance of closest right seat,
        // for any vacant seat, we pick the seat with max separation.
        occupied = INT_MAX;
        for(int i = seats.size()-1; i >= 0; i--) {
            if(seats[i] == 0) {
                int right_dist = occupied == INT_MAX ? INT_MAX : occupied - i;
                max_dist = max(max_dist, min(left_dist[i], right_dist));
            }
            else
                occupied = i;
        }
        return max_dist;
    }
};
