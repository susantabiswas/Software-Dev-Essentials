```
/*
	https://leetcode.com/problems/contiguous-array/
	
	The idea is to maintain a counter variable that accounts for 0s and 1s. 
	Increment by 1 for 1 and decrement by 1 for 0.
	For an initial value x given to counter var,
	counter = x
	We will see the counter becoming x again when the number of 1s and 0s are same between the interval.
	So whenver we see the same counter value that means in between those indices equal nums of 0s and 1s occurred. So diff(curr_idx - last_seen_idx_for_same_counter_val) gives use the sequence length, do this while traversing the array.
	
	TC: O(N), SC: O(N)
*/

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        // count, index: this count is the net count of zeros(-) and 1(+)
        unordered_map<int, int> value_idx;
        // baseline value 0 is taken before the array start, this is because
        // we need an initial reference value to compare back when we encountered
        // equal number of 0s and 1s.
        value_idx[0] = -1;
        int max_len = 0;
        int counter = 0;
        
        // for any 0, we reduce by 1 the counter and for 1 we increase by 1
        for(int i = 0; i < nums.size(); i++) {
            counter = counter + (nums[i] == 1 ? 1 : -1);
            // check if the same counter value was encountered before
            if(value_idx.find(counter) != value_idx.end()) {
                int curr_len = i - value_idx[counter];
                max_len = max(max_len, curr_len);
            }
            else
                value_idx[counter] = i;
        }
        return max_len;
    }
};
```
