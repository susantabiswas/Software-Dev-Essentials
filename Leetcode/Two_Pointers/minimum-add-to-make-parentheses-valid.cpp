/*
    https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/
    
    Solution 1: Stack
    TC: O(N)
    SC: O(N)
    
    Solution 2: Two pointers
    TC: O(N)
    SC: O(1)
    
    Solution 3: Counter
    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    // SOL 1: Stack
    int stackSol(string &S) {
        /*
            Idea is to find pair of balancing bracket pairs.
            Using a stack we try to save the positional information
            of chars seen so far at any point during traversal. If for the current 
            char the last seen char forms a balanced pair, we remove them from consideration
            and continue. Since we have info about previously seen chars by position
            we can handle recursive balancing cases as well.
        */
        stack<char> seq;
        for(const char& c: S) {
            // balanced pair found, so remove
            if(!seq.empty() && c == ')' &&
               seq.top() == '(')
                seq.pop();
            else
                seq.push(c);
        }
        return seq.size();
    }
    
    // SOL 2: Two pointers
    int twoPointersSol(string &S) {
        /*
            We start the traversal with a pointer for writing the char
            and one for traversal. Thw writing index can write either ( or ) when
            it is unbalanced.
            The writing index is always pointing to the position where the new char should be written, 
            so we check if current traversal pos and last written char form a balanced 
            pair, if they do then we need to exclude the current and last added 
            char. This is done by moving a step back for writing ptr and not adding curr char.
            Finally if there are any unbalcned brackets, write idx > 0
        */
        // points to the position where the latest char should be added
        int write_idx = 0;
        for(int curr = 0; curr < S.size(); curr++) {
            // balanced pair found, so we ignore both 
            if(write_idx > 0 && S[curr] == ')'
              && S[write_idx-1] == '(')
                write_idx -= 1;
            else
                S[write_idx++] = S[curr];
        }
        return write_idx;
    }
    
    // SOLUTION 3: Counter
    // TC: O(n)
    // SC: O(1)
    int counterSol(string s) {
        // Tracks how many ( unbalanced have appeared
        // Whenever a matching closing ) is found, the count is decreased
        // to indicate a balanced pair of ()
        int unbalanced_opening = 0;
        // ) for which there are no opening (
        int req = 0;
        
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '(')
                ++unbalanced_opening;
            // Balance out as many matching opening (
            // as possible
            else if(unbalanced_opening > 0)
                --unbalanced_opening;
            // There are no opening ( that can match the current ),
            // so an insert operation is required
            else
                ++req;
        }
        return req + unbalanced_opening;
    }
    
    int minAddToMakeValid(string S) {
        // return stackSol(S);
        // return counterSol(S);
        return twoPointersSol(S);
    }
};
