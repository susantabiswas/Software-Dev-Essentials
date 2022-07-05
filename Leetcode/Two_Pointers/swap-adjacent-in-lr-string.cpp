/*
    https://leetcode.com/problems/swap-adjacent-in-lr-string/
    
    Things to note:
    1. Based on the swap patterns, L can be moved to left in presence of X
    2. R can be moved right in presence of X
    
    So that means it is only possible to swap and reach end iff each L in start lies atleast
    >= position compared to end and each R in start should be <= position compared to end.
    This is again due to the fact that L can only move left and R can move right.
    
    So we start traversal ignoring the X and focus on the breaking cases, if we don't find any breaking cases
    then it is possible.
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    bool twoPointerSol(string start, string end) {
        // both the strings have be of same size
        if(start.size() != end.size())
            return false;
        
        int n = start.size();
        int i = 0, j = 0;
        
        while(i < n && j < n) {
            // Get past all the X since these help move L or R
            while(i < n && start[i] == 'X')
                ++i;
            while(j < n && end[j] == 'X')
                ++j;
            
            // traversal finished, so it must be possible
            if(i == n && j == n)
                return true;
            
            // if the curr char is not same, then there is no way to match 
            if(start[i] != end[j])
                return false;
            
            // If both point to R, then start's ptr should be <= end's ptr since
            // R can move towards right
            if(start[i] == 'R' && i > j)
                return false;
            
            // If both point to L, then start's ptr should be >= end's ptr since
            // L can move towards left
            if(start[i] == 'L' && i < j)
                return false;
            ++i, ++j;
        }
        
        // We might still have some chars left for one of the strings
        // Eg start = XXXXL, end = XLXXX 
        // 'i' will end first. So let the indices get past X and then check if they both finished processing
        while(i < n && start[i] == 'X')
            ++i;
        while(j < n && end[j] == 'X')
            ++j;

        return i == j;
    }
    
    bool canTransform(string start, string end) {
        return twoPointerSol(start, end);
    }
};
