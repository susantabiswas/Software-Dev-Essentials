/*
    https://leetcode.com/problems/generate-parentheses/submissions/
*/
class Solution {
public:
    // Using backtracking
    // TC: O(2^n), SC: O(n!)(Recursive stack)
    void generateParenthesisArrangements(string curr, int left,
                                         int right, vector<string>& parenthesis) {
        // when there are no parenthesis left
        if(left == 0 && right == 0) {
            parenthesis.emplace_back(curr);
            return;
        }
        
        // there are two options for putting the current parenthesis, 
        // either pick a left or right
        if(left > 0)
            generateParenthesisArrangements(curr + '(', left - 1, right, parenthesis);
        // A right ) is only pput when there are less number of (, so as to ensure that
        // there is a ( for balancing the )
        if(left < right && right > 0)
            generateParenthesisArrangements(curr + ')', left, right - 1, parenthesis);
    }
    
    vector<string> generateParenthesis(int n) {
        vector<string> parenthesis;
        int left = n, right = n;
        string curr;
        
        generateParenthesisArrangements(curr, left, right, parenthesis);
        return parenthesis;
    }
};
