/*
    https://leetcode.com/problems/jump-game-iii/
    
    TC: O(n)
    SC: O(n/2) ~ O(n), for each node, 2 nodes are added, this forms a binary tree level each time.
    So the worst case is the last level of this binary which can have max n/2 nodes.
    
    Idea is to do BFS and find the path that starts from the start index to any index with val 0.
*/
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        queue<int> q;
        unordered_set<int> visited;
        
        q.emplace(start);
        visited.insert(start);
        
        while(!q.empty()) {
            auto idx = q.front();
            q.pop();
            
            if(arr[idx] == 0)
                return true;
            
            // forward jump
            if(idx + arr[idx] < arr.size() && !visited.count(idx + arr[idx])) {
                q.emplace(idx + arr[idx]);
                visited.insert(idx + arr[idx]);
            }
            // backward jump
            if(idx - arr[idx] >= 0 && !visited.count(idx - arr[idx])) {
                q.emplace(idx - arr[idx]);
                visited.insert(idx - arr[idx]);
            }
        }
        return false;
    }
};
