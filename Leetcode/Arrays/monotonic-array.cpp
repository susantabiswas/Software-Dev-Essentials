/*
    https://leetcode.com/problems/monotonic-array/submissions/
*/

class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        // keeps track of monotonically increasing and decreasing trends
        bool increasing = true, decreasing = true;
        
        for(int i = 1; i < A.size() && (increasing || decreasing);
            i++) {
            // check if the any of the trends become invalid or not
            if(A[i-1] < A[i])
                decreasing = false;
            if(A[i-1] > A[i])
                increasing = false;
        }
        
        return increasing || decreasing;
    }
};
