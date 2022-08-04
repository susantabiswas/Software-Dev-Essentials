/*
    https://leetcode.com/problems/permutations-ii/
    
    TC: O(nPr)/x1!x2!, where x1 and x2 are no. of instances of duplicates. The
        code doesnt do repeatitive computations with duplicates and hence the formula.
    SC: O(N), max recursive call stack depth
    
    Although very similar to https://leetcode.com/problems/permutations/ problem.
    The solution used there with 2 swaps and nums array passed by ref doesnt work with duplicates.
    
    The logic for pmt1, pmt 2, cmb sum 1 problem are all very similar with subtle differences which are hard 
    to reason.
    
    Reason:
    Permutations I problem:
        Here we have distinct elements. Since we want all the permutations the following logic works:
        
        // swap the current position with remaining numbers
        for(int i = curr; i < nums.size(); i++) {
                // swap positions
                swap(nums[curr], nums[i]);
                permuteUniqueRec(nums, curr + 1, pmt);
                // revert back
                swap(nums[curr], nums[i]);
        }
        
        Here each time for the curr pos, we are swapping it with each number and recurse for the remaining
        numbers. Due to swapping the curr position is swapped with all the numbers, it ensures that all combinations of
        numbers and positions are explored.
        1,2,3
        curr = 0
        1,2,3, i = 1 => [2,3]
        2,1,3, i = 1 => [1,3]
        3,2,1, i = 2 => [2,1] => since all elements are distinct, the inner pmts are always unique
        
        NOTE: Even if the input array was sorted, due to the swapping the sorted order is not maintained.
                This is the biggest diff to note while dealing with duplicates.
                
        nums[1:N-1] will again repeat the process and will do pmt of nums[1:N-1] after this recursive call.
        Here swapping twice reverts the changes made between curr and ith position and this is okay since we 
        just want to put each number once at the current position, nothing else.
        
    
    Combinations Sum II problem: https://leetcode.com/problems/combination-sum-ii/
        Here we have duplicates and the core problem is find a subset with given target sum.
        Each step of recursive call is doing this:
        {..existing subset..} + Curr Num
        Since we can have duplicates we need to ensure that Curr Num used with a given subset is done
        only once, otherwise we will have duplicate subsets.
        
        To avoid this, we compare the last processed (added) number with the current ith number, we only
        allow an element to be pushed to the subset iff that same element hasn't pushed earlier with the 
        current subset
        
        for(int i = curr; i < nums.size(); i++) {
            // for ith position pick the 1st instance of uniq
            // num incase of duplicates
            if(i == curr || nums[i] != nums[i-1]) {
                subset.emplace_back(nums[i]);
                findCmb(i+1, sum + nums[i], target, nums, subset, result);
                subset.pop_back();
            }
        }
        
        
    Permutations II problem:
    
        Now at a glance this problem looks like a combination of above two problems and hence combining there logic
        should work. But it doesn't work.
        Combined logic: Doesn't work
        
        // swap the current position with remaining numbers
        for(int i = curr; i < nums.size(); i++) {
            if(i == curr || nums[i] != nums[i-1]) {
                // swap positions
                swap(nums[curr], nums[i]);
                permuteUniqueRec(nums, curr + 1, pmt);
                // revert back
                swap(nums[curr], nums[i]);
            }
        }
        With duplicates and pmt where all the elements needs to be part of the final result, the above logic fails.
        Things to note:
        Assuming: input array is sorted
        
        1. We need a way to skip the duplicates for the current position. For this to work, we need to ensure
        that the elements are in sorted order => same elements will be put together. Now due to the second swap,
        the orig number at curr is put back after an iteration of for loop, then the smaller curr element is compared
        against much bigger numbers and not immediate numbers, which after swapping makes the array unsorted.
        1,2,3
        curr = 0
        1,2,3, i = 1 => [2,3]
        2,1,3, i = 1 => [1,3], 1 comapred with 2 is find since they are immediate and swapping will retain the sorted order
        3,2,1, i = 2 => [2,1], 1 compared with 3 and swapped
        
        This implies that 2nd swap is not needed.
        
        2. if(i == curr || nums[i] != nums[i-1]) this condition is only valid when elements are sorted.
        eg: 1,1,1,2,2,3,3
        curr = 0
        1,1,1,2,2,3,3, i = 0
        3,1,1,2,2,1,3, i = 5 => here 1s are no longer together and hence nums[i] != nums[i-1] won't work.
        Hence this can happen:
        curr = 1
        3,1,[1,2,2,1,3], i = 1
        3,1,[1,2,2,1,3], i = 5 => nums[4] != nums[4-1] so swapping between 1 at idx=1 and 1 at idx=5 will happen and
        result is duplicate remaining subset
        
        3. Why if(i == curr || nums[i] != nums[i-1]) doesn't work with a single swap but if(i == curr || nums[curr] != nums[i]) does?
        1,1,2,2,3,3
        curr = 0
        i = 2, nums[2] = 2, nums[2-1] = 1 => nums[i] != nums[i-1] is true
        So it will swap, 2,1,1,2,3,3
        i = 3, nums[3] = 2, nums[3-1] = 1 => nums[i] != nums[i-1] is true
        Since we compared only with the last, we got 1 at previous 2's place after swapping and now the nums[curr] != nums[i] also is true due to that.
        This would result in a swap which shouldnt happen, now again 2 at idx = 3 is put at 0th index and would create a duplicate
        2,1,1,2,3,3
        
        4. Correct logic:
            for(int i = curr; i < nums.size(); i++) {
                if(i == curr || nums[curr] != nums[i]) {
                    swap(nums[curr], nums[i]);
                    findPmt(curr + 1, nums, result);
                }
            }
            
            nums[curr] is compared with ith number, since we dont swap back 2nd time, the next greater element stays at 
            curr position and next time its next greater element is compared with it and swapped. Since immediate elements
            are compared, on swapping they are put at correct positions and order is maintained.
            
            orig: [1,2,2,3,3]
            curr = 0
            1,[2,2,3,3], i = 0
            2,[1,2,3,3], i = 1
            3,[1,2,2,3], i = 2
            The remaining subset is always sorted since the result from last swap is not reverted back.
            and since the elements are still sorted, if cond works and avoids duplicates.
*/
class Solution {
public:
    void findPmt(int curr, vector<int> nums,
            vector<vector<int>>& result) {
        // all elements processed
        if(curr == nums.size()) {
            result.emplace_back(nums);
            return;
        }
        
        for(int i = curr; i < nums.size(); i++) {
            // the below code ensures that even after swapping nums[curr+1:N-1] is sorted
            // this is only possible because we are swapping only once, each time the smaller number
            // is compared with its next biggest and after swapping is put to the 1st instance of that.
            // In next iteration again the 2nd biggest number at curr is compared with 3rd biggest and 
            // swapped similarly maintaining the sorted order.
            // E.g: Orig: 1,2,2,3
            // curr = 0
            // 1,[2,2,3], i = 0
            // 2,[1,2,3], i = 1
            // 3,[1,2,2], i = 2
            // Notice how all the elements after curr=0 are still sorted and since they are sorted
            // (i == curr || nums[curr] != nums[i]) will work. As this check can only work when the duplicates are
            // put together. In an unsorted order, it won't work.
            if(i == curr || nums[i-1] != nums[i]) {
                swap(nums[curr], nums[i]);
                findPmt(curr + 1, nums, result);
            }
        }
    }
    
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        findPmt(0, nums, result);
        
        return result;
    }
};