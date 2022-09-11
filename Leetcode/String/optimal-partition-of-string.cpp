/*
    https://leetcode.com/problems/optimal-partition-of-string/
    
    TC: O(n)
    SC: O(26)~ O(1)
    
    We would need a new partition whenever we see a repeated char of ongoing 
    substring. The moment we see a repeated char, we can't continue with the ongoing substring and hence we end the partition there and begin with a new partition.
*/
class Solution {
public:
    int partitionString(string s) {
        // tracks char freq
        unordered_map<char, int> freq;
        int min_parts = 0;
        int start = 0, end = 0;
        
        while(end < s.size()) {
            ++freq[s[end]];
            
            // repeated char seen, end the partition
            if(freq[s[end]] > 1) {
                min_parts++;
                // Current char is repeated so starting from curr
                // char we start a new partition
                start = end;
                // Remove previous partition data
                freq.clear();
                // Add the 1st char freq of new partition
                ++freq[s[end]];
            }
            ++end;
        }
        // since we only update partition number when a duplicate is seen,
        // last parition wont be counted. So add +1
        return min_parts + 1;
    }
};
