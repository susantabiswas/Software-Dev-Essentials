/*
    https://leetcode.com/problems/largest-number/
    TC: O(nlogn * L), L = max combined length of any two numbers
        ~ O(nlogn), since L < 50 for current problem
*/
class Solution {
public:
    // custom comparator
    // For strings of same length, then lexographically bigger is simply the
    // answer. But for strings of diff lengths, just finding lexographically gives
    // wrong answer. Eg: 350, 35, lexographical answer: 350 comes before 35, which is wrong
    // So we combine the strings and then compare lexographically
    struct Comparator {
        bool operator()(int& a, int& b) const {
            string first = to_string(a), second = to_string(b);
            return (first + second) > (second + first);
        } 
    };
    
    string largestNumber(vector<int>& nums) {
        Comparator comp;
        // sort the array with custom comparator
        sort(nums.begin(), nums.end(), comp);
        
        // form the string number
        string largest_number;
        for(const int& el: nums)
            largest_number += to_string(el);
        // remove all preceeding zeros except for the last position, if 
        // all the digits are zero, leave one
        int pos = 0;
        while(pos < largest_number.size()-1 && largest_number[pos] == '0')
            ++pos;
        return largest_number.substr(pos);
    }
};
