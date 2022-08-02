/*
    https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
    
    Stack Solution:
        Since we remove 2 chars if they are same and adjacent or if there is a even numbered
        char group in between. So we need a way to save the previous information of chars based
        on their position, for which stack is a perfet companion. With a stack we can save the 
        position information, so even if there is a even numbered group of duplicates, once they
        are removed we will still have info about the last pushed just before the start of the 
        duplicate window.

        TC: O(N)
        SC: O(N)
        
    Two pointers:
        we maintain two pointers: write_idx: latest char write position in result
        curr_idx: currently traversed char idx
        
        The idea is whenever curr idx is equal to last written position, then it means
        a duplicate has been found, so we dont add current char to ans and also the 
        the last char added is amongst the duplicates so we do --write_idx.
        TC: O(N)
        SC: O(1)
*/
class Solution {
public:
    // SOL 1
    string stackSol(string &S) {
        stack<char> s;
        
        for(char &c: S) {
            // last seen char is same, so discard that and dont include current as well
            if(!s.empty() && s.top() == c) 
                s.pop();
            else
                s.emplace(c);
        }
        
        // build the entire string and reverse it 
        string result;
        while(!s.empty()) {
            result += s.top();
            s.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
    
    // SOL 2
    string twoPointers(string &S) {
        int write_idx = 0, curr_idx = 0;
        
        while(curr_idx < S.size()) {
            // Last added char is a duplicate of current, so ignore both
            if(write_idx > 0 && S[write_idx-1] == S[curr_idx]) 
                write_idx -= 1;
            else
                S[write_idx++] = S[curr_idx];
            ++curr_idx;
        }
        
        return S.substr(0, write_idx);
    }
    
    string removeDuplicates(string S) {
        // return stackSol(S);
        return twoPointers(S);
    }
};
