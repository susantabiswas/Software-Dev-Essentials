/*
    https://leetcode.com/problems/determine-if-two-events-have-conflict/
*/
class Solution {
public:
    bool isOverlapping(pair<int, int>& t1, pair<int, int>& t2) {
        return t2.first <= t1.second && t2.second >= t1.second;    
    }
    
    bool haveConflict(vector<string>& event1, vector<string>& event2) {
        pair<int, int> t1 = { stoi(event1[0].substr(0, 2)) * 60 + stoi(event1[0].substr(3, 2)),
                              stoi(event1[1].substr(0, 2)) * 60 + stoi(event1[1].substr(3, 2))
                             };
        pair<int, int> t2 = { stoi(event2[0].substr(0, 2)) * 60 + stoi(event2[0].substr(3, 2)),
                              stoi(event2[1].substr(0, 2)) * 60 + stoi(event2[1].substr(3, 2))
                             };
        
        
        return isOverlapping(t1, t2) || isOverlapping(t2, t1);
    }
};
