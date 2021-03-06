/*
    https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/submissions/
*/
class Solution {
public:
    int minDays(int n) {
        int days = 0;
        queue<int> q;
        unordered_set<int> visited;
        
        int n_level = 1;
        q.emplace(n);
        
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            --n_level;
            
            if(visited.count(curr) == 0) {
                if(curr == 0)
                    break;    
            
                visited.emplace(curr);
                
                if(curr % 2 == 0) 
                    q.emplace(curr / 2);
                if(curr % 3 == 0)
                    q.emplace(curr / 3);
                q.emplace(curr - 1);
            }
            if(n_level == 0) {
                ++days;
                n_level = q.size();
            }
        }
        return days;
    }
};
