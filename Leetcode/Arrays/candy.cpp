/*
    https://leetcode.com/problems/candy/
    
    TC: O(n)
    SC: O(n)
    
    Core idea is to - to find the candies required, we only need the info about the left and right neighbors.
    So imagine this problem in two halves, one where if decide the candies required based
    on left neighbor only and next part where we find the candies required based on the righ neighbor.
    
    For ith child, the candies req is max (left, right) based candy requirement.
    
    Also doing traversal in one particular direction at a time ensures that the only influence on 
    child 'i' is from one side. Eg going from left to right, for ith child, we are only deciding based on
    left and also the left child was not influenced by its right child which is 'i'.
*/
class Solution {
public:
    int candy(vector<int>& ratings) {
        int candies = 0;
        
        int n = ratings.size();
        vector<int> req(n, 1);
        
        // decide the candies only based on left neighbor
        for(int i = 0; i < n; i++)
            if(i-1 >= 0 && ratings[i] > ratings[i-1])
                req[i] = req[i-1] + 1;
        
        // since for ith child, we know how many candies are required based
        // on his left neighbor, we start iterating from right to know the candies 
        // req purely based right neighbor
        // Then decide the actual candies req with both the neighbor's rating
        for(int i = n-1; i >= 0; i--) {
            if(i+1 < n && ratings[i+1] < ratings[i])
                req[i] = max(req[i], req[i+1] + 1);
            
            candies += req[i];
        }
        
        return candies;
    }
};
