/*
    https://leetcode.com/problems/first-bad-version/
    
    We can use binary search for doing this. Search space is [1:n], goal is to find the first defective version.
	We set low=1 and high=n. Now all the versions after the first defective are all also defective, so take out the 
	mid and check if it is defective, if it is not that means we are before the first defective one so go right, 
	else if it is defective go left till we end the search space. Since our high will always point to a defective version, 
	so in the end high + 1 gives the first defective.
    
    TC: O(logN), SC: O(1)
*/

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    // Using Binary search
    // TC: O(logn)
    int firstBadVersion(int n) {
        int low = 1, high = n;
        
        while(low <= high) {
            int mid = low + (high - low) / 2;
            // current version number is one without defect, so set the low a the next version
            if(!isBadVersion(mid))
                low = mid + 1;
            // while the version is defective, go left
            else
                high = mid - 1;
        }
        return high + 1;
    }
};
