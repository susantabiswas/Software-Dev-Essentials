/*
    https://leetcode.com/problems/make-the-string-great/
    
    Solution 1: Stack
    TC: O(N)
    SC: O(N)
    
    Solution 2: Two pointers
    TC: O(N)
    SC: O(1)
*/

class Solution {
public:
    // SOL 1
    string stackSol(string &s) {
        /*
            Using a stack we try to save the positional information
            of chars seen so far at any point during traversal. If for the current 
            char the last seen char forms a bad pair, we remove them from consideration
            and continue. Since we have info about previously seen chars by position
            we can handle recursive deletion cases as well.
        */
        stack<char> past_chars;
        
        for(int i = 0; i < s.size(); i++) {
            // bad  pair found
            if(!past_chars.empty() && 
               past_chars.top() != s[i] && // when diff chars, check if their lower case is same 
               tolower(past_chars.top()) == tolower(s[i]))
                past_chars.pop();
            else
                past_chars.emplace(s[i]);
        }
        
        // construct the ans from remaining chars
        string result;
        while(!past_chars.empty()) {
            result += past_chars.top();
            past_chars.pop();
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
    
    // SOL 2
    string twoPointersSol(string &s) {
        /*
            We start the traversal with a pointer for writing the ans
            and one for traversal. The writing index is always pointing 
            to the position where the new char should be written, so we 
            check if current traversal pos and last written char form a bad 
            pair, if they do then we need to exclude the current and last added 
            char. This is done by moving a step back for writing ptr and not adding curr char.
        */
        // points to the position where the latest char should be added
        int write_idx = 1;
        
        for(int curr_idx = 1; curr_idx < s.size(); curr_idx++) {
            // if bad pair found
            if(write_idx > 0 && s[write_idx-1] != s[curr_idx] && 
              tolower(s[write_idx-1]) == tolower(s[curr_idx]))
                write_idx -= 1;
            else
                s[write_idx++] = s[curr_idx];
        }
        return s.substr(0, write_idx);    
    }
    
    string makeGood(string s) {
        //return stackSol(s);
        return twoPointersSol(s);
    }
};
