/*
    https://leetcode.com/problems/maximum-split-of-positive-even-integers/
    
    TC: O(num^0.5)
    2 + 4 + 6 + ....2 * i = S
    2(1 + 2 + 3 + .... i) = S
    2(i*(i + 1) / 2) = S
    i*(i + 1) = S
    ~ i^2 = S
    ~ i = (S)^1/2
    
    Greedily pick the numbers from 2 and subsequent numbers 4, 6 till we find that it is not possible to add the next even number to make the entire sum.  The remaining sum is just added as a number since it is ensured to be even.
    
*/
class Solution {
public:
    vector<long long> maximumEvenSplit(long long sum) {
        vector<long long> nums;
        if(sum % 2)
            return nums;
        
        for(int num = 2; ; num += 2) {
            // check if adding the next number will be possible. If it is not possible add the remaining even sum as the number
            if(num + 2 > sum - num) {
                nums.emplace_back(sum);
                break;
            }
            else
                nums.emplace_back(num);
            sum -= num;
        }
        return nums;
    }
};
