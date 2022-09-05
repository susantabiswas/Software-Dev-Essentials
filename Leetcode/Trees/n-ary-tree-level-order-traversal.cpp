/*
    https://leetcode.com/problems/n-ary-tree-level-order-traversal/
    
    TC: O(N)
    SC: O(N)
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> traversal;
        vector<int> level;
        queue<Node*> q;
        // Only add the root if it is not null
        if(root)
            q.emplace(root);
        
        int level_nodes = q.size();
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            // process the current node
            level.emplace_back(curr->val);
            --level_nodes;
            
            // add its children
            for(auto child: curr->children)
                q.emplace(child);
            
            // end of level
            if(level_nodes == 0) {
                level_nodes = q.size();
                traversal.emplace_back(move(level));
            }
        }
        return traversal;
    }
};
