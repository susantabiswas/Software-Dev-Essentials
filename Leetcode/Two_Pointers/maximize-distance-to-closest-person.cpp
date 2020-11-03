/*
    https://leetcode.com/problems/maximize-distance-to-closest-person/submissions/
    
    Solution 1: Uses O(N) extra space
    Solution 2: Uses O(1) space 
*/

class Solution {
public:
    // SOLUTION 1
    /*
    Idea is to save the dist of nearest left filled seat pos. for
    each of the vacant seats. 
    Then do a backward traversal from right and compare the distance of
    left and right filled seat distances for each vacant seat. Keep
    track of max such distance
    TC: O(N)
    SC: O(N)
    */
    int sol1(vector<int> &seats) {
        // dist fo filled seat nearest to seat pos. 'i'
        vector<long> left_dist(seats.size(), 0);
        long closest_filled = -1, max_dist = INT_MIN;
        
        // find the closest left filled seat distance
        for(int i = 0; i < seats.size(); i++) {
            // dist from the last filled left seat,
            // in case current seat is filled, it is 0
            left_dist[i] = i - closest_filled;
            // if current seat is taken
            if(seats[i])
                closest_filled = i;
        }
        
        // since the leftmost seat wont have anybody on its left, we make
        // dist = +INF
        left_dist[0] = INT_MAX;
        
        /// backward traversal 
        closest_filled = INT_MAX;
        long closest_dist = 0;
        for(int i = seats.size()-1; i >= 0; i--) {
            if(!seats[i]) {
                // vacant seat found, check the distance of its 
                // left and right nearest filled seats
                closest_dist = min(left_dist[i], closest_filled - i);
                max_dist = max(max_dist, closest_dist);
            }
            // update closest right side seat pos.
            if(seats[i])
                closest_filled = i;
        }
        return max_dist;
    }
    
    // SOLUTION 2
    // TC: O(N)
    // SC: O(1)
    int sol2(vector<int> &seats) {
        long left_occupied = INT_MIN, right_occupied = 0;
        long max_dist = 0;
        
        for(int i = 0; i < seats.size(); i++) {
            // occupied seat
            if(seats[i])
                left_occupied = i;
            else {
                // now check for the first occupied seat on right
                while(right_occupied <= i ||
                     right_occupied < seats.size() && 
                     seats[right_occupied] == 0) {
                    ++right_occupied;
                }
                // if there are no filled seats on right, then only the left
                // distance should matter so we give right side dist a very large value
                right_occupied = right_occupied >= seats.size() ? INT_MAX : right_occupied;
                // check the dist if current seat is used
                max_dist = max(max_dist, min(i - left_occupied, 
                                            right_occupied - i));
            }
        }
        
        return max_dist;
    }
    
    int maxDistToClosest(vector<int>& seats) {
        // return sol1(seats);
        return sol2(seats);
    }
};
