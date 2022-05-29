/*
    https://leetcode.com/problems/merge-triplets-to-form-target-triplet/
    
    TC: O(N)
    SC: O(1)
    
    Thing to note is, as long as an operation allows a value out of (a, b, c) to reach
    a higher value such that it is <= to the corresponding value in (x, y, z), we can do the 
    operation. So we take out all the triplets which are allowed to do the operation.
    These triplets don't have any individual (a, b, c) > (x, y, z) as once a bigger value is
    reached we can't go back.
*/
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        // candidate triplet with init values
        vector<int> candidate = {-1, -1, -1};
        
        for(auto triplet: triplets) {
            // check if the current triplet can be considered for operartion
            if(triplet[0] <= target[0] && triplet[1] <= target[1] &&
              triplet[2] <= target[2]) {
                candidate = {max(candidate[0], triplet[0]),
                            max(candidate[1], triplet[1]),
                            max(candidate[2], triplet[2])};
            }
        }
        return candidate == target;
    }
};
