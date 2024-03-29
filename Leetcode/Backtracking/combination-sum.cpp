/*
    https://leetcode.com/problems/combination-sum/
    
    TC: O(n ^ (target / min el of candidates)), in each recursive call, n calls are
    made and the depth is equal to max number of elements in the subset that sum to target,
    which is target / min el of candidates
    SC: O(target / min el of candidates), worst case scenario is when the
        smallest element is used to sum upto target. 
        eg target=3, [1,4] => [1,1,1]
*/
class Solution {
public:
    void cmb(int curr, vector<int> partial, int target,
            vector<int>& nums, vector<vector<int>>& result) {
        // base case
        if(target < 0)
            return;
        // subset found with req target sum
        if(target == 0) {
            result.emplace_back(partial);
            return;
        }
        if(curr == nums.size())
            return;
        
        // since a number can be used multiple times, we recurse for
        // all positions starting curr and don't necessarily force it start
        // from i+1 in next call, instaed give it the choice of reusing the
        // ith number again
        for(int i = curr; i < nums.size(); i++) {
            partial.emplace_back(nums[i]);
            cmb(i, partial, target - nums[i], nums, result);
            partial.pop_back();
        }
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        sort(candidates.begin(), candidates.end());
        cmb(0, vector<int>{}, target, candidates, result);
        return result;
    }
};

///////////////////////////////// Way 2
    // TC: O(2 ^ max(n, target / min el of candidates)), 
    // one recursive call only increases the index which can go till 'n',
    // the other recursive call can happen for target / min el times, so the worst
    // case is whichever is greater 
    // SC: O(max(n, target / min el of candidates))
    void sol(int curr, int target, vector<int>& cmb, vector<int>& nums,
            vector<vector<int>>& result) {
        if(target == 0) {
            result.push_back(cmb);
            return;
        }
        
        if(target < 0)
            return;
        
        if(curr == nums.size())
            return;

        // Exclude the current element
        sol(curr+1, target, cmb, nums, result);
        cmb.push_back(nums[curr]);

        // Include the current element
        sol(curr, target - nums[curr], cmb, nums, result);
        cmb.pop_back();
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> cmb;
        sol(0, target, cmb, candidates, result);
        
        return result;
    }
