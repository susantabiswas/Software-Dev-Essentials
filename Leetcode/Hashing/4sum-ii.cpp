/*
    https://leetcode.com/problems/4sum-ii/
*/
class Solution {
public:
    /// TC: O(N^2)
    int fourSumCount(vector<int> a, vector<int> b,
                    vector<int> c, vector<int> d) {
        // create a hash table of all pair combinations of first two arrays
        // key: sum, value: no. of times the sum was seen
        unordered_map<int, int> two_sum;
        int total = 0;
        
        // store sum pair of first two arrays
        for(const auto& first: a)
            for(const auto& second: b) {
                int sum = first + second;
                if(two_sum.find(sum) == two_sum.end())
                    two_sum.emplace(sum, 0);
                ++two_sum[sum];
            }
        
        // since a + b + c + d = 0 needs to be found
        // => a + b = -(c + d)
        // store a + b pairs, and for all cmb of c and d,
        // we check if there is -(c + d) in the hash table
        for(const int& third: c) {
            for(const int& fourth: d) {
                int sum_to_find = -1 * (third + fourth);
                // check how many pairs have the required sum
                // current combination can combine with that many pairs for 0 sum
                auto it = two_sum.find(sum_to_find);
                
                if(it != two_sum.end())
                    total += it->second;
            }
        }
        
        return total;
    }    
};
