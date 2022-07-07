/*
    https://leetcode.com/problems/sort-integers-by-the-power-value/
    
    For each number, we can use the formula to compute the power. To avoid repeatitive 
    calculation, we use a DP cache to save the results. Finally to give the kth number in sorted list
    we use partition algo from quick sort.
    
    This is known as Collatz conjecture.
    Time complexity is not known for this, but for n < 2^68 it is finite.
*/
class Solution {
public:
    // Finds the power of an integer + DP
    int power(int n, unordered_map<int, int>& dp) {
        if(dp.count(n) == 0) {
            int steps = 0;
        
            while(n != 1) {
                n = n % 2 ? (3 * n + 1) : n / 2;
                ++steps;
            }
            
            dp[n] = steps;
        }
        return dp[n];
    }
    
    int getKth(int lo, int hi, int k) {
        vector<pair<int, int>> powers;
        // <num, power>
        unordered_map<int, int> dp;
        
        // Compute the power for each number
        for(int num = lo; num <= hi; num++)
            powers.emplace_back(make_pair(power(num, dp), num));
        
        // Since we only need the nth number, we can use partition algorithm used in quick sort
        // to sort the kth number
        nth_element(powers.begin(), powers.begin() + k - 1, powers.end());
        return powers[k-1].second;
    }
};
