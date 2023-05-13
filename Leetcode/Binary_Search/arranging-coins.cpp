/*
    https://leetcode.com/problems/arranging-coins/
    
    We use binary search to search the row for which the coins are utilized the
    most. To evaluate the directtion to move we use a function that gives the remaining
    coins when used for filling k rows.
    
    TC: O(logn)
*/

class Solution {
public:
    // TC: O(1)
    // Finds the coins remaining/needed to fill all n stairs
    int coinsRemaining(long long n, int total_coins) {
        long long coins_req = (long long) (n * (n + 1) * 0.5);
        return total_coins - coins_req;
    }
    
    int arrangeCoins(int coins) {
        // High limit is set to rough estimate of n using sum formula
        long long low = 0, high = sqrt((long long)coins*2 + 1);
        while(low < high) {
            // We take a ceil rounding 
            int row = low + (high - low + 1) / 2;
            long long coins_rem = coinsRemaining(row, coins);
            
            // If coins 
            if(coins_rem >= 0)
                low = row;
            else
                high = row - 1;
        }
        return low;
    }
};
