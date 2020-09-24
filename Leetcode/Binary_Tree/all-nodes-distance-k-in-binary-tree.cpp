/*
    https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/submissions/
    
    Idea is to convert the tree to a bidirectional graph. Once we have a graph representation
    of nodes, we can do BFS from the target node till K levels and return the nodes in Kth level.
    
    TC: O(V + E)
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void createGraph(TreeNode *root, 
             unordered_map<TreeNode*, vector<TreeNode*>> &g) {
        if(root) {
            if(root->left) {
                g[root].emplace_back(root->left);
                g[root->left].emplace_back(root);
                createGraph(root->left, g);
            }
            if(root->right) {
                g[root].emplace_back(root->right);
                g[root->right].emplace_back(root);
                createGraph(root->right, g);
            }
        }
    }
    
    vector<int> bfs(unordered_map<TreeNode*, vector<TreeNode*>> &g,
                   TreeNode *src, int K) {
        
        if(!src)
            return {};
        
        queue<TreeNode*> q;
        q.emplace(src);
        int level = 0, n_level = q.size();
        // for keeping track of visited nodes
        unordered_set<TreeNode*> visited;
        // mark source as visited
        visited.emplace(src);
        
        while(!q.empty()) {
            // distance reached
            if(level == K)
                break;

            TreeNode *curr = q.front();
            q.pop();
            --n_level;
                
            // add the unvisited neighbors
            for(auto vertex: g[curr]) {
                if(visited.count(vertex) == 0) {
                    q.emplace(vertex);
                    visited.emplace(vertex);
                }
            }
            // end of level
            if(n_level == 0) {
                ++level;
                n_level = q.size();
            }
            
        }
        
        vector<int> level_nodes;
        while(!q.empty()) {
            level_nodes.emplace_back(q.front()->val);
            q.pop();
        }
        
        return level_nodes;
    }
    
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        // convert the tree to an adjaceny graph
        unordered_map<TreeNode*, vector<TreeNode*>> g;
        // create the bidirectional graph
        createGraph(root, g);
        
        // do BFS from target node and get the k distant nodes
        return bfs(g, target, K);
    }
};
