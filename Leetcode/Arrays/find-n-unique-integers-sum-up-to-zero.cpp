/*
    https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/submissions/
*/
class Solution {
public:
    /*
        Since we just need 'n' terms and total sum = 0.
        So we add a +ve and -ve of that term, that makes 2 terms.
        In case n is odd: add [1:n/2], [-1:-n/2] and 0
        In case n is even: add [1:n/2], [-1:-n/2]
    */
    vector<int> sumZero(int n) {
        vector<int> arr;
        // if n is odd, add zero and decrement it to account for zero
        if(n % 2 != 0)
            arr.emplace_back(0), --n;
        
        // add the positive and negative terms
        for(int i = 1; i <= n/2; i++) {
            arr.emplace_back(i);
            arr.emplace_back(-1 * i);
        }
        return arr;
    }
};
