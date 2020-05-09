/*
	https://leetcode.com/problems/valid-perfect-square/
	
    Find the sq root of number and check if floor of that value is same as sq root
    or not. For a perfect sq there shouldnt be any difference. Since we compare float 
    number, we use relative comparison.
*/
class Solution {
public:
    bool isPerfectSquare(int num) {
        double sqrt_num = sqrt(num);
        return fabs(sqrt_num - floor(sqrt_num)) < numeric_limits<double>::epsilon() * sqrt_num;
    }
};
