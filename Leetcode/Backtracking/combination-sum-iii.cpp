/*
    https://leetcode.com/problems/combination-sum-iii/
    
    Time Complexity: 
    O(k * C(9, k))
    O(k * 9! / (9−k)!k!)
    
        In a worst scenario, we have to explore all potential combinations to the very end, i.e. the sum n is a large number (n > 9∗9). 
        At the first step, we have 9 choices, while at the second step, we have 8 choices, so on and so forth.
        C(9, k) = 9 choose k, which is ways of choosing k numbers from 9, where the order doesn matter. In the code we can only
        explore one order and not all the orders for the same set of numbers. Eg [1,2] is explored only not [2,1] hence it is Cmb not Pmt.
        
        The number of exploration we need to make in the worst case would be C(9,K) = 9!(9−K)!k!, assuming that K<=9K<=9. 
        By the way, K cannot be greater than 9, otherwise we cannot have a combination whose digits are all unique.
        Each exploration takes a constant time to process, except the last step where it takes O(K) time to make a copy of combination.
        To sum up, the overall time complexity of the algorithm would be 9!(9−K)!k! * k

        Reason it is not O(k * 9^k) is because, after each kth call we are not necessarily left with k-1 elements. Eg when n=7 is picked, we are left with
        only [8,9] for the next call, so saying T(k) = 9*T(k-1) is misleading as there will be 9 calls only in the 
        1st time recursion starts.
        O(k * 9^k) > C(9, k) 
    
    Space Complexity: O(K)
        During the backtracking, we used a list to keep the current combination, which holds up to K elements, i.e. O(K).

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
