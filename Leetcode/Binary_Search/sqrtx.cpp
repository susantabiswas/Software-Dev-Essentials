/*
    https://leetcode.com/problems/sqrtx/
    
    We use binary search for this. We set the lower limit as 0 and upper limit as n/2.
    n/2 ensures that the range covers all possible candidates for sq root, since sq root is
    m * m, so n/2 * n/2 > n and hence covers all.
    
    TC: O(logn)

    The formula for mid is diff because in the Binary search lower limit is always set to mid 
    and not mid+1, that means in case we are stuck with just two numbers and left is the answer,
    mid formula will always pick the left and left will not move forward and hence the loop
    will get stuck in infinite loop.

    Eg
    [1,2,3,4]

    finally, low=2, high=3
    With low + (high - low) / 2, we get mid = 2 and after that low stays at 2 since low = mid

    By modifying the formula to low + (high - low + 1) / 2, we get the right side element i.e 3,
    so low will move forward and wont get stuck.

    Crux is for the side of limit that is equal to mid, we modify the formula such that mid always picks the other 
    side when we are left with 2 numbers.
    Like here low was equal to mid, so modifying the mid formula we always get the right side element when
    there are 2 elements left and ensures that movement happens.
*/

class Solution {
public:
    int mySqrt(int x) {
        if(x <= 1)
            return x;
        int low = 0, high = ceil(x / 2);
        
        while(low < high) {
            // rounded ceil
            int mid = low + (high - low + 1) / 2;
            long long sq = (long long)mid * mid;
            if(sq <= x)
                low = mid;
            else
                high = mid - 1;
        }
        
        return low;
    }
};
