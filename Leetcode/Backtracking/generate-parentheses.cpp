/*
    https://leetcode.com/problems/generate-parentheses/
*/
class Solution {
public:
    // Using backtracking, Since we only form valid parenthesis and not all cmbs of 
    // parenthesis, we no. of valid parenthesis = nth Catalan no.
    // Had we created all cmbs of parenthesis and checked if it is a valid one when length 
    // becomes 2n, then we would have generated 2^ n cmbs and then the TC would have been O(n * 2^n)

    // TC: O(n * Cn), Cn = Nth Catalan Number of valid sequences and it takes n to copy it to the result
    // Cn = 1 / (1+n) * C(2n, n)
    // Cn = 1/(1+n) * (2n)!/n!n!
    // bound: 4^n / sqrt(n)
​
    // SC: O(n)(Recursive stack), O(Cn + n) if result is also accounted
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
