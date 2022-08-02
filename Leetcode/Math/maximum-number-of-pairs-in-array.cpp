/*
    https://leetcode.com/problems/maximum-number-of-pairs-in-array/
    
    Find the no. of instances for each number. For a given number with frequency f > 1,
    it can have f-1 numbers that can form pairs if f is odd.
    So for each number, add the even pairs that can be formed out of it and update
    the left out counter by 1 if it is odd.
    TC: O(N)
    SC: O(M), M = no. of unique numbers
*/
class Solution {
public:
    vector<int> numberOfPairs(vector<int>& nums) {
        unordered_map<int, int> freq;
        for(auto num: nums)
            ++freq[num];
        
        vector<int> result(2);
        
        for(auto [num, count]: freq) {
            result[0] += count / 2;
            result[1] += count % 2;
        }
            
        return result;
    }
};
