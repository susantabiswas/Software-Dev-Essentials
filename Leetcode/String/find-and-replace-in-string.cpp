/*
    https://leetcode.com/problems/find-and-replace-in-string/
    
    TC: O(n)
    SC: O(n)
    
    Naive solution is to apply the operation in the original string with an insert at
    that position replacing the substring, this can be O(n^2).
    
    To do the operations in O(n), we keep a vector of strings. Each position is meant for 
    storing the final set of chars that start from that position.
    Initially each position is filled with the individual chars of string 's'.
    Then we apply the replace opeartions and save the result. Finally construct the string from
    this array.
*/
class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        int N = s.size();
        // str_op[i] = final chars that should start from i
        vector<string> str_op(N);
        // Store all the chars as string in the array
        for(int i = 0; i < N; i++)
            str_op[i] = s[i];
        
        // Apply the operations for the indices
        for(int i = 0; i < indices.size(); i++) {
            int src_len = sources[i].size();
            // If the substring's length at source is out of limit 
            if(indices[i] + src_len > N)
                continue;
            
            // check if the substring at source and orig str match
            if(s.substr(indices[i], src_len) == sources[i]) {
                // apply the operation
                str_op[indices[i]] = targets[i];
                // mark the rest of the indices involved as empty
                for(int j = 1; j < src_len; j++)
                    str_op[indices[i] + j] = "";
            }
        }
        
        string result;
        
        for(auto str: str_op)
            result += str;
        return result;
    }
};
