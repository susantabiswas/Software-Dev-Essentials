/*
    https://leetcode.com/problems/evaluate-reverse-polish-notation/
    
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    int evaluate(int a, int b, string op) {
        if(op == "+")
           return a + b;
        if(op == "-")
           return a - b;
        if(op == "*") 
           return a * b;
        if(op == "/")
           return a / b;
        return 0;
    }
    
    int evalRPN(vector<string>& tokens) {
        stack<int> value;
        
        for(auto token: tokens) {
            cout << token<<" ";
            // if an operator
            if(token == "+" || token == "-" || token == "/" || token == "*") {
                // operand 1
                int num2 = value.top();
                value.pop();
                // operand 2
                int num1 = value.top();
                value.pop();
                // evaluate the operands with operator
                int res = evaluate(num1, num2, token);
                value.push(res);
            }
            else 
                value.push(stoi(token));
        }
        return value.top();
        
    }
};
