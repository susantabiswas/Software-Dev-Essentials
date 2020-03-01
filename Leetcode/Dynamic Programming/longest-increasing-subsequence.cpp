/*
    https://leetcode.com/problems/longest-increasing-subsequence/
    
    LIS using binary search
    TC: O(nlogn)
*/
class Solution {
public:
    // Maintain an array of numbers increasing order. Initially empty.
    // Idea is traverse the array, for a given position 'i', find the first greater number
    // than current in that array using binary search, if there is no such number add current to that array.
    // If a number is found greater than current don't add to that array. 
    // In the end that array will be filled with numbers in increasing order
    int lisBinarySearch(vector<int>& nums) {
        // vector for storing longest increasing subsequence
        vector<int> lis;
        for(const int& num: nums) {
            // find the first number greater than current in LIS
            auto it = lower_bound(lis.begin(), lis.end(), num);
            
            // if no such number is found, we can add the current
            if(it == lis.end()) {
                lis.emplace_back(num);
            }
            // if a number greater exists, then replace it with current, this is
            // because putting the smaller number in place of a bigger number will allow
            // more numbers greater than current to be part of LIS
            else if(*it > num)
                *it = num;
        }
        return lis.size();
    }
    
    
    int lengthOfLIS(vector<int>& nums) {
        return lisBinarySearch(nums);
    }
};
