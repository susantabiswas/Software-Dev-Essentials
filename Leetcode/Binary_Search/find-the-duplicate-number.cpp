/*
    https://leetcode.com/problems/find-the-duplicate-number/
*/
class Solution {
public:
    // Using Binary search
    // TC: O(nlogn), SC: O(1)
    int binarySearchSolution(vector<int>& nums) {
        // The idea is that it is known that there is a duplicate, so 
        // we can use pigeon hole concept here. We do binary search on the search
        // space of [1:N], then count the number of elements <= middle. If the 
        // duplicate is on the left side, then count should be more than mid,
        // else it is on the right side. Initially search space is [1: N], then
        // each time narrow down the search space
        int left = 1, right = nums.size() - 1;
        while(left < right) {
            int mid = left + (right - left) / 2;
            
            // count the number of elements smaller/ equal than middle element
            int c = 0;
            for(const int& el: nums)
                if(el <= mid)
                    ++c;
            
            if(c > mid)
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
    
    // Using Sorting
    // TC: O(nlogn)
    int sortingSolution(vector<int>& nums) {
        // sort the numbers and find the number which has duplicate
        // by checking the one which has the same at next position
        sort(nums.begin(), nums.end());
        
        int duplicate = 0;
        for(int i = 0; i < nums.size() - 1; i++)
            if(nums[i] == nums[i+1]) {
                duplicate = nums[i];
                break;
            }
        return duplicate;
    }
    
    int findDuplicate(vector<int>& nums) {
        // return sortingSolution(nums);
        return binarySearchSolution(nums);
    }
};
