/*
    https://leetcode.com/problems/permutations/
    
    Two solutions :
    1. Backtracking based:
    https://leetcode.com/problems/permutations-ii/discuss/481076/c-backtracking-solution
    2. Using next permutation:
    https://leetcode.com/problems/permutation-sequence/discuss/480860/c-beats-100-time-wise-explained
*/
class Solution {
public:
    // Using backtracking
    // TC: O(n!), SC: O(n! * n)
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
    
    // Using backtracking
    vector<vector<int>> permuteBacktracking(vector<int>& nums) {
        set<vector<int> > s;
        vector<vector<int> > pmt;
        permuteUniqueRec(nums, 0, s, pmt);
        return pmt;
    }
    
    // Using next permutation each time
    // TC: O(n!), SC: O(1)
    vector<vector<int> > nextPermutationDriver(vector<int>& nums) {
        // sort the numbers so that all thepermutations come
        sort(nums.begin(), nums.end());
        vector<vector<int> > pmt;
        pmt.emplace_back(nums);
        
        while(true) {
            // find the first not in descending order from right side
            int i = nums.size() - 2;
            while(i >= 0 && nums[i] >= nums[i+1])
                --i;
            // no next pmt possible
            if(i < 0)
                break;
            // find the first number from right greater than current
            for(int j = nums.size() - 1; j > i; j--)
                if(nums[j] > nums[i]) {
                    // swap position and reverse nums[i+1 : N-1]
                    swap(nums[i], nums[j]);
                    reverse(nums.begin() + i + 1, nums.end());
                    break;
                }
            pmt.emplace_back(nums);
        }
        return pmt;
    }
    
    vector<vector<int>> permute(vector<int>& nums) {
        // return permuteBacktracking(nums);
        return nextPermutationDriver(nums);
    }
    
};
