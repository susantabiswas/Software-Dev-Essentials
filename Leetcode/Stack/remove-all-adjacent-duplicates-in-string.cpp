/*
    https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
    
    Since we remove 2 chars if they are same and adjacent or if there is a even numbered
    char group in between. So we need a way to save the previous information of chars based
    on their position, for which stack is a perfet companion. With a stack we can save the 
    position information, so even if there is a even numbered group of duplicates, once they
    are removed we will still have info about the last pushed just before the start of the 
    duplicate window.
    
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    string removeDuplicates(string S) {
        stack<char> s;
        
        for(char &c: S) {
            if(!s.empty() && s.top() == c) 
                s.pop();
            else
                s.emplace(c);
        }
        
        string result;
        while(!s.empty()) {
            result += s.top();
            s.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
