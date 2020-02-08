/*
    https://leetcode.com/problems/increasing-triplet-subsequence/
    
    Two solutions:
    1. Two pointers
    2. Binary search
*/
class Solution {
public:
    
    // Solution 1: two pointers
    // TC: O(N)
    
    // Idea is keep track of smallest two numbers, ensuring min1 < min2.
    // If at any point we find a number 'n', such that n > min1 and n > min2, that makes a triplet
    // else if n < min1, min1 = n, or if n > min1 and n < min2, min2 = n.
    // If we are not able to find a triplet till position 'i', we can safely update the min values to even smaller
    // value just making sure that min1 < min2.
    bool increasingTripletTwoPointers(vector<int>& nums) {
        // keeps track of smallest two numbers, such that min1 < min2
        int min1 = numeric_limits<int> :: max(), min2 = numeric_limits<int> :: max();
        
        for(const int& num : nums) {
            // if current is smaller/equal(otherwise same number might go to min2) than min1, update it
            if(num <= min1)
                min1 = num;
            // current is greater than min1 but smaller/equal than min2, that makes min1 < min2 > num,
            // so update min2
            else if(num <= min2)
                min2 = num;
            // current is greater than min2, min1 < min2 < num
            else if(num > min2)
                return true;
        }
        return false;
    }
    
    // Solution2 : Binary Search
    // TC: O(nlog2)
    
    // Maintain an array of numbers increasing order. Initially empty.
    // Idea is traverse the array, for a given position 'i', find the first greater number
    // than current in that array using binary search, if there is no such number add current to that array.
    // If a number is found greater than current don't add to that array. 
    // In the end that array will be filled with numbers in increasing order
    bool increasingTripletBSearch(vector<int>& nums) {
        // vector for storing longest increasing subsequence
        vector<int> lis;
        for(const int& num: nums) {
            // find the first number greater than current in LIS
            auto it = lower_bound(lis.begin(), lis.end(), num);
            
            // if no such number is found, we can add the current
            if(it == lis.end()) {
                lis.emplace_back(num);
                // check if a triplet is found
                if(lis.size() == 3)
                    return true;
            }
            // if a number greater exists, then replace it with current, this is
            // because putting the smaller number in place of a bigger number will allow
            // more numbers greater than current to be part of LIS
            else if(*it > num)
                *it = num;
        }
        return false;
    }
    
    
    bool increasingTriplet(vector<int>& nums) {
        //return increasingTripletBSearch(nums);
        return increasingTripletTwoPointers(nums);
    }
    
    
};
