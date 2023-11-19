/*
    https://leetcode.com/problems/the-kth-factor-of-n/
    
    SOLUTION 1: When you want to find all the factors
    
    TC: O(sqrt(n) * ( 2 * log(2 * sqrt(n))) + k)
    (Iteration * (Two push operations in set, worst case the size of set will be 2*sqrt(n)) + k iterations)
    
    O(sqrt(n) * log(sqrt(n)))
    
    Factors of a number occur in pairs:
    small * big = n
    ......
    big * small = n
    
    A * B = n
    
    Basically if a factor is small, then its other part will be larger to make it equal to n
    and as we increase A, B will decrease and so on.
    Once A = sqrt(n), B will also be sqrt(n) as sqrt(n) * sqrt(n) = n
    
    So we iterate till sqrt(n), and we check if the current A can divide n or not, if it does
    then push both A and B in the set.
    We use a set since it is easier to find the Kth element because of its sorted nature.
    
    SOLUTION 2: Minor Optimization
    Ensure set size is atmost k
    
    TC: O(sqrt(n) * log(min(k, sqrt(n))))
    SC: O(k)
    
*/
class Solution {
public:
    int kthFactor(int n, int k, bool k_factors_only = true) {
        set<int> factors;
            
        int limit = sqrt(n);
        
        for(int factor = 1; factor <= limit; factor++) {
            if(n % factor == 0) {
                factors.insert(factor);
                factors.insert(n / factor);
            }
            
            if(k_factors_only && factors.size() > k)
                factors.erase(*factors.rbegin());
        }
        
        if(k > factors.size())
            return -1;
        
        // go to the kth number in sorted set
        auto it = factors.begin();
        k -= 1;
        while(k--)
            ++it;
        
        return  *it; 
    }
};
