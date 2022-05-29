/*
    https://leetcode.com/problems/combination-sum-iii/
    
    TC: O(k * 9^k), k elements to copy + max 9 recursive calls with max depth k
    SC: O(k)
*/
class Solution {
public:
    void cmb(int curr, int n, int k, vector<int> partial,
            vector<vector<int>>& result) {
        // base case
        if(k == 0 && n == 0) {
            result.emplace_back(partial);
            return;
        }
        // when we have overshot the req sum, but can still have elements to subset
        if(n <= 0)   
            return;
        // when we have reached max number of elements that can be put, but not target
        if(k <= 0)
            return;
        // from current position, one by one put each of the remaining numbers
        // to current subset
        for(int i = curr; i <= 9; i++) {
            partial.emplace_back(i);
            cmb(i+1, n-i, k-1, partial, result);
            partial.pop_back();
        }
    }
    
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        cmb(1, n, k, vector<int>{}, result);
        return result;
    }
};
