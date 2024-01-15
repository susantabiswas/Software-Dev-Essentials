/*
    https://leetcode.com/problems/multiply-strings/
    
    TC: O(mn)
    SC: O(m + n)
    m and n are size of num1 and num2 respectively
*/
class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        vector<int> num(m + n, 0);
        
        // if either of the nums is 0, result is 0
        if((m == 1 && num1[0] == '0') or
          (n == 1 && num2[0] == '0'))
            return "0";
        
        // start multiplying digit by digit
        for(int i = m-1; i >= 0; i--) {
            for(int j = n-1; j >= 0; j--) {
                int prod = (num1[i] - '0') * (num2[j] - '0');
                
                // instead of using carry and keeping track of each digit at each level,
                // we directly forward the carry to the next position. Sum is updated
                // continuously, since we are essentially adding all the digits of all the
                // levels for a ith position, it is okay to directly add the digit for that position.
                num[i + j + 1] += prod;
                num[i + j] += num[i + j + 1] / 10;
                num[i + j + 1] %= 10;
            }    
        }
        
        // skip the leading 0s
        int i = 0;
        while(i < num.size() && num[i] == 0)
            ++i;
        
        // convert to string
        string res;
        while(i < num.size()) 
            res += (num[i++] + '0');
        
        return res;
    }
};
