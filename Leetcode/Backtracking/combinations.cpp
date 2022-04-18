/*
    https://leetcode.com/problems/combinations/
    
    We need to form subsets and ensure that size == k. We start traversal from 
    curr = 1. For each recursive call, we traverse through all the numbers that have
    not been added and one by one put it at the curr position in subset and then
    recurse further till subset = k.
*/
class Solution {
public:
    // TC: O(n * n!/(n-k)!), in the end it takes O(n) to copy the array elements to array
    // SC: P(n! / (n - k)!)
    void findCmb(int curr, int k, int& n, vector<int> partial,
                vector<vector<int>>& cmb) {
        // base case: when we have a subset of size k
        if(k == 0) {
            cmb.emplace_back(partial);
            return;
        }
        // for each element we have 2 choices: either include or exclude
        for(int i = curr; i <= n; i++) {
            partial.emplace_back(i);
            findCmb(i+1, k-1, n, partial, cmb);
            partial.pop_back();
        }
    }
    
    vector<vector<int>> combine(int n, int k) {
        // saves all possibe combinations
        vector<vector<int>> cmb;
        findCmb(1, k, n, vector<int>{}, cmb);
        return cmb;
    }
};
