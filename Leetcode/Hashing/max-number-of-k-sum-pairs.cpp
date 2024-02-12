/*
    https://leetcode.com/problems/max-number-of-k-sum-pairs/
    
    TC: O(n)
    SC: O(n)
    
    2 Sum solutions - Hashing, Sorting both can be used for solving this.
    
    Idea is just to find the pairs and then exclude both the numbers.
*/
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        
        int result = 0;
        
        for(auto num: nums) {
            
            // if we have seen the complementary number before, we
            // can use that and the current number to form a pair
            if(freq.count(k - num)) {
                ++result;
                
                if(--freq[k - num] == 0) {
                    freq.erase(k - num);
                }
            }
            else
                ++freq[num];
        }
        return result;
    }
};
