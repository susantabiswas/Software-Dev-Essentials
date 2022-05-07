/*
    https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
    
    Solution 1: Stack
    Whenever the problem asks for grouping similar chars to do something without 
    changing the order of chars, chances are stack is involved.
    
    Here also, we need a way to know if there is a group of similar elements of size k.
    Idea is to associate the instance count with each char, everytime we process a char,
    we set its init count=1, then check if similar chars are present before this. If
    same chars exists before this, we make its count = count of previous instance + 1.
    
    When we reach a count = k, we start removing the chars.
    TC: O(N)
    SC: O(N)
    
    Solution 2: Two pointers
	
	Idea is to keep writing the chars while keeping track of no. of instances of that char
	that exists before in continuous manner. If at any point a group of k chars are formed, move the
	write index k positions back, this effectively ignores all these k chars.
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    // Sol1 : Stack
    string stackSol(string str, int k) {
        // <ch, no. of ch chars till including current in continuous manner>
        stack<pair<char, int>> s;
        
        for(char ch: str) {
            // init count for curr char type
            int count = 1;
            // check how many chars of same type exists just before
            if(!s.empty() && s.top().first == ch)
                count = s.top().second + 1;
            s.emplace(make_pair(ch, count));
            // if the current makes the count = k, remove all the previous k-1 elements
            if(count == k) {
                while(!s.empty() && s.top().first == ch)
                    s.pop();
            }
        }
        
        // form the string from stack, reverse the output to get the original order
        string result;
        while(!s.empty()) {
            result += s.top().first;
            s.pop();
        }
        reverse(result.begin(), result.end());
        
        return result;
    }
    
    // Sol 2: Two pointers
    string twoPointersSol(string &str, int k) {
        // write_idx: Position to write an element
        int write_idx = 0, curr_idx = 0;
        // char_count[i] = no. of instances of curr char that exists in continuous manner before
        vector<int> char_count(str.size(), 0);
        
        for(; curr_idx < str.size(); curr_idx++, write_idx++) {
            str[write_idx] = str[curr_idx];
            // check if there exists same chars before
            char_count[write_idx] = write_idx > 0 && str[write_idx] == str[write_idx-1] ? char_count[write_idx-1] + 1 : 1;
            // if a group of same chars of size k has formed
            if(char_count[write_idx] == k)
                write_idx -= k;
        }
        
        return str.substr(0, write_idx);
    }
    
    string removeDuplicates(string str, int k) {
        // return stackSol(str, k);
        return twoPointersSol(str, k);
    }
};
