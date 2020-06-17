/*
    https://leetcode.com/problems/guess-number-higher-or-lower/submissions/
    
    This is a binary search problem, where the guess
    function is the comparator
        
    TC: O(logn)
*/

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        int low = 1, high = n, mid = 0;
        
        while(low <= high) {
            mid = low + (high - low) / 2;
            int comparison = guess(mid);
            
            if(comparison == 0)
                break;
            else if(comparison == -1)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return mid;
    }
};
