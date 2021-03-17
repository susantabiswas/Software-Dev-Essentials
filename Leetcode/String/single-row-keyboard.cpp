/*
    https://leetcode.com/problems/single-row-keyboard/submissions/
    
    Idea is to save the position of each char in keyboard and then
    iterate through the chars in word one by one and each time take the
    diff of pos of that char with last char position.
    TC: O(N)
    SC: O(26)
*/
class Solution {
public:
    int calculateTime(string keyboard, string word) {
        unordered_map<char, int> pos;
        // save the position of each char in keyboard
        for(int i = 0; i < keyboard.size(); i++)
            pos[keyboard[i]] = i;
        
        int last_pos = 0, time_req = 0;
        for(char &c: word) {
            time_req += abs(last_pos - pos[c]);
            last_pos = pos[c];
        }
        return time_req;
    }
};
