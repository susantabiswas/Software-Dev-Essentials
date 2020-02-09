/*
    https://leetcode.com/problems/contains-duplicate-ii/
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        // we use a hash table to store the index of a number
        // Then while traversing the array we get a number which is 
        // already in hash table, tehn find the difference of index to check if < k
        unordered_map<int, int> arr_idx;
        for(int i = 0; i < nums.size(); i++) {
            // if number already exists, check the diff
            if(arr_idx.find(nums[i]) != arr_idx.end()) {
                // check the diff of positions
                if(i - arr_idx[nums[i]] <= k)
                    return true;
            }
            // update the index
            arr_idx[nums[i]] = i;
        }
        return false;
    }
};
