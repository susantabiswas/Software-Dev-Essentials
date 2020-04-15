/*
    https://leetcode.com/submissions/detail/324980139/?from=/explore/challenge/card/30-day-leetcoding-challenge/529/week-2/3299/
*/
class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int net_shift = 0;
        const int N = s.size();
        
        // find the resultant shift, left is taken -ve and right is +ve
        for(auto op: shift)
            net_shift += op[0] == 0 ? -1 * op[1] : op[1];
        // set the final shift operation
        bool right = net_shift > 0 ? true : false;
        // only take the actual shifts req
        net_shift = abs(net_shift) % N;
        string result;
        
        // if right shift: reverse(terms_to_shift) + reverse(terms_before_shifting_terms)
        if(right) {
            reverse(s.end() - net_shift, s.end());
            reverse(s.begin(), s.end() - net_shift);
        }
        // if right shift: reverse(terms_after_shifting_terms) + reverse(terms_to_shift)
        else {
            reverse(s.begin() + net_shift, s.end());
            reverse(s.begin(), s.begin() + net_shift);
        }
        
        // finally reverse the entire string to get the effect of shifting
        reverse(s.begin(), s.end());
        return s;
    }
    
    string stringShift1(string s, vector<vector<int>>& shift) {
        int net_shift = 0;
        const int N = s.size();
        
        // find the resultant shift, left is taken -ve and right is +ve
        for(auto op: shift)
            net_shift += op[0] == 0 ? -1 * op[1] : op[1];
        // set the final shift operation
        bool right = net_shift > 0 ? true : false;
        // only take the actual shifts req
        net_shift = abs(net_shift) % N;
        string result;
        
        // if right shift: terms_to_shift + terms_before_shifting_terms
        if(right)
            result = s.substr(N - net_shift, net_shift) + s.substr(0, N - net_shift);
        // if right shift: terms_after_shifting_terms + terms_to_shift
        else
            result = s.substr(net_shift, N - net_shift) + s.substr(0, net_shift);
        
        return result;
    }
};
