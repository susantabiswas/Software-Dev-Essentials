/*
    https://leetcode.com/problems/bitwise-and-of-numbers-range/submissions/
    TC: O(32) ~ O(1), SC: O(1)
*/
// for a number x, its next two numbers are even and odd or vice-versa.
// i.e next number is formed left shifting x by 1 and putting 0/1 in LSB.
// So for [m, n], we start looking at the bit positions from end till
// both the numbers have same bits remaining or if one of them is finished.

// When bits are diff, AND for that pos will be 0 when m < n, since to reach n,
// m will have numbers in between which includes odd and even consecutive numbers that
// will just make the AND of that position 0.

// Once we know the no. of different bits between m and n, we can shift whatever bits are left of smaller 
// number m by that many places to get the number
// m:110, n:111, diff: last bit and after shifting m:11, n:11
// so to account for the 0bits on left side and right shifting
// m << 1 => 11 << 1 => 110 which is the ans

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int diff_bits = 0;
        // while remaining bits are diff
        while(m < n) {
            ++diff_bits;
            m >>= 1;
            n >>= 1;
        }
        return m << diff_bits;
    }
};
