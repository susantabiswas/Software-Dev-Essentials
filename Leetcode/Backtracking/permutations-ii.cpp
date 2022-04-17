/*
    https://leetcode.com/problems/permutations-ii/submissions/
    
    For each number position 'i', to get all the permutations with the N-i numbers,
    we need to swap each of the numbers with ith number once , add it to the current pmt,
    repeat the same for the remaining numbers.
    
    TC: O(n * n!), we are doing n * (n-1) * (n-2) .. (1) recursive calls => O(n!)
    then at each call(n), we run the for loop n times and at leaf nodes, again n times
    T(n) = n * T(n-1) 
    SC: (n! * n)
*/
class Solution {
public:
    void permuteUniqueRec(vector<int>& nums, int curr,  
                          set<vector<int>>& s, vector<vector<int> >& pmt) {
        // if all the numbers have been used
        if(curr == nums.size()) {
            if(s.find(nums) == s.end()) {
                s.emplace(nums);
                pmt.emplace_back(nums);
                return;
            }
        }
        
        // swap the current position with remaining numbers
        for(int i = curr; i < nums.size(); i++) {
            // don't swap with same numbers, except we are doing it with itself
            if(i == curr || nums[i] != nums[curr]) {
                // swap positions
                swap(nums[curr], nums[i]);
                permuteUniqueRec(nums, curr + 1, s, pmt);
                // revert back
                swap(nums[curr], nums[i]);
            }
        }
    }
    
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        set<vector<int> > s;
        vector<vector<int> > pmt;
        permuteUniqueRec(nums, 0, s, pmt);
        return pmt;
    }
};
