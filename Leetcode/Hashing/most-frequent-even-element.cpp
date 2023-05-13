/*
    https://leetcode.com/problems/most-frequent-even-element/
    
    TC: O(N)
    SC: O(N)
    
    Track the frequency of each num using a hash table. Keep track of current 
    candidate for answer, if an even number with higher freq or smaller number with same
    freq is seen, update.
*/
class Solution {
public:
    int mostFrequentEven(vector<int>& nums) {
        int smallest = INT_MAX, smallest_even_freq = 0;
        unordered_map<int, int> freq;
        
        for(auto num: nums) {
            ++freq[num];
            // If the num is even and it's freq is greater than max or
            // equal to max but is smaller than the most frequent even num
            if(num % 2 == 0 && (freq[num] > smallest_even_freq ||
                freq[num] == smallest_even_freq && smallest > num)) {
                smallest = num;
                smallest_even_freq = freq[num];
            }
        }
        return smallest == INT_MAX ? -1 : smallest;
    }
};
