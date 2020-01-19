/*
    https://leetcode.com/problems/fraction-to-recurring-decimal/submissions/
*/
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if(numerator == 0)
            return "0";
        
        unordered_map<int, int> prev;
        long long remainder = 0;
        string result;
        
        if(denominator < 0 ^ numerator < 0)
            result += '-';
        long long  dividend = labs(static_cast<long long>(numerator));
        long long divisor = labs(static_cast<long long>(denominator));
        
        result += to_string(dividend / divisor);
        remainder = dividend % divisor;

        if(remainder == 0)
            return result;
        
        result += '.';
        while(remainder != 0) {
            if(prev.find(remainder) != prev.end()) {
                result.insert(prev[remainder], "(");
                result += ')';
                break;
            }
            
            prev.emplace(remainder, result.size());
            remainder *= 10;
            result += to_string(remainder / divisor);
            remainder = remainder % divisor;
        }
        return result;
    }
};
