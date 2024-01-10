/*
    https://leetcode.com/problems/solving-questions-with-brainpower/
    
    TC: O(n)
    SC: O(n)
    
    Main idea is - 
        Either solve a question
        Skip a question
        
    Now if we do that from left to right, it won't work because of value leakage.
    
    Below code doesn't work, because skip is just max(skip_prev, solve_prev) and so
    it might take up solve_prev and pass on to right elements even if that previous solved question 
    has brainpower > those right elements(right elements are not allowed if that previous question is solved)
    
    E.g [[100, 10], [1, 1], [1, 90]]
    Expected: 100
    Output: 190 (since 1st element's skip leakes the value 100 from previous question and passes to 2nd element's skip,
    even though if 1st is solved, we can't solve next 10 questions)
    
    long long mostPoints(vector<vector<int>>& questions) {
        if(questions.empty())
            return 0;
        
        int n = questions.size();
        // solve[i] = pts[i] + 1st elemnt's (solve, not) on left that allows this to be solved
        // not[i] = max(solve[i-1], not[i-1])
        vector<long> solve(n, 0), skip(n, 0);
        
        solve[0] = questions[0][0];
        
        for(int i = 1; i < n; i++) {
            solve[i] = questions[i][0];
            
            int j = i-1;
            while(j >= 0) {
                
                if(questions[j][1] + j < i) {
                    solve[i] += max(solve[j], skip[j]);
                    break;
                }
                --j;
            }
            skip[i] = max(solve[i-1], skip[i-1]);
        }
        
        return max(solve.back(), skip.back());
    }
    
*/
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        if(questions.empty())
            return 0;
        
        int n = questions.size();
        // pts[i] = Max pts that can be accumulated if we start from ith question (need not be solved, just start)
        vector<long> pts(n, 0);
        
        // We start from right to left to avoid value leakage as seen in left to right
        pts[n-1] = questions[n-1][0];
        
        for(int i = n-2; i >= 0; i--) {
            // if we start at current question, we have 2 choices:
            // 1. Solve it - we get the pt for current question and then we can skip the next
            //      brainpower no. of questions and add the score after that question
            // 2. Skip it - We accumalate the score from the i+1th question
        
            long solve = questions[i][0] + (i + questions[i][1] + 1 < n ? pts[i + questions[i][1] + 1] : 0);
            long skip = pts[i+1];
            
            pts[i] = max(solve, skip);
        }
        
        return pts.front();
    }
};
