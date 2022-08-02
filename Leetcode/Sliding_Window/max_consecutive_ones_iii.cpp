/*
    Find longest sequence of 1s with limited number of flips
    1004. Max Consecutive Ones III
    https://leetcode.com/problems/max-consecutive-ones-iii/
    
    We use two pointers to keep track of start and end of current window. We expand
    till all the flips have been used and another zero is encountered, then shrink the window
    till no. of zeros is under control. After that update the max length if applicable.
*/

class Solution {
public:
    int longestOnes(vector<int>& arr, int K) {
        int flips = K;
        int i = 0, j = 0;
        int max_len = 0;
        
        while(i < arr.size()) {
            // expansion
            if(arr[i++] == 0) {
                --flips;
            }
            // shrinkage
            while(flips < 0) {
                if(arr[j++] == 0)
                    ++flips;
            }
            
            // update max length
            if(max_len < (i-j)) {
               max_len = i - j;
            }
        }
        return max_len;
    }
};

/////////////////////////////////
/*
    https://leetcode.com/problems/max-consecutive-ones-iii/
*/
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int max_ones = 0, ones = 0;
        
        int n = nums.size();
        int start = 0, end = 0;
        
        while(end < n) {
            // expand the window till k is positive
            if(k >= 0) 
                k = (nums[end++] == 1 ? k : k-1);  
            // shrink to make the window safe
            if(k < 0)
                k = (nums[start++] == 1 ? k : k+1);
            
            max_ones = max(max_ones, end - start);
        }
        return max_ones;
    }
};
