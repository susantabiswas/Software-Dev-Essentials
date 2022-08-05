/*
    https://leetcode.com/problems/restore-ip-addresses/
    
    TC: O(3^4) ~ (1), we make 3 calls for in each stage and at max do this for 
                        no. of parts of ip number which is 4 parts controlled by part_num
    SC: O(4) ~ O(1), we recurse only for max of 4 levels
    
    Try to simulate the rules as closly as possible.
    For each sub range of ip, we use a mthod to validate.
    For the curr char, we create 3 substrings s[curr:curr], s[curr:curr+1], s[curr:curr+2]
    then with those substrings, recurse further.
*/
class Solution {
public:
    // check if a number is valid for ip subpart
    bool isValid(string s) {
        if(s.empty() || (s.size() > 1 && s[0] == '0'))
            return false;
        // now that we know 01 like strs won't appear, we need 
        // to confirm that it has valid digits and the final number >= 0 and <= 255
        int num = 0;
        for(char& ch: s) {
            if(!isdigit(ch))
                return false;
            num = num*10 + (ch - '0');
        }
        return num >= 0 && num <= 255;
    }
    
    void validIp(int curr, string& s, string ip, 
                 int part_num, vector<string>& result) {
        // base case: when all 4 parts have been made, but there
        // are still digits left. eg: orig: 12112334 => 1.2.1.123 34
        if(part_num == 5 && curr < s.size())
            return;
        // base case: all the numbers covered and all the parts exists i.e 4
        if(curr == s.size() && part_num == 5) {
            result.emplace_back(ip);
            return;
        }
        
        // if there are already existing subparts before
        if(!ip.empty())
            ip += '.';
        
        for(int i = 0; i < 3 && curr + i < s.size(); i++) {
            string ip_part = s.substr(curr, i + 1);
            if(isValid(ip_part))
                validIp(curr+i+1, s, ip + ip_part, part_num+1, result);
        }
    }
    
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        validIp(0, s, "", 1, result);
        return result;
    }
};