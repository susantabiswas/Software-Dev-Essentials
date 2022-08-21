/*
    https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/
    
    Idea is to simply convert the tree to an undirected graph.
    Once it has been converted to an undirected graph, the problem becomes "traverse the graph from 
    starting node". Using BFS we can also keep track of the levels, the final level is the time required.
    TC: O(N)
    SC: O(N)
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // Creates an undirected graph from tree
    void postorder(TreeNode* root, unordered_map<int, vector<int>>& graph) {
        if(root) {
            postorder(root->left, graph);
            postorder(root->right, graph);
            
            // parent -> child
            // child -> parent
            if(root->left) {
                graph[root->val].emplace_back(root->left->val);
                graph[root->left->val].emplace_back(root->val);
            }
            if(root->right) {
                graph[root->val].emplace_back(root->right->val);
                graph[root->right->val].emplace_back(root->val);
            }
        }    
    }
    
    // Finds the no. of levels to traverse the entire tree from start node
    int bfs(int start, unordered_map<int, vector<int>>& graph) {
        queue<int> q;
        q.emplace(start);
        // keeps track of current level and no. of nodes in the current level
        int level = 0, level_nodes = q.size();
        unordered_set<int> visited;
        visited.emplace(start);
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            --level_nodes;
            
            // add all unvisited neighbors
            for(auto neighbor: graph[curr]) {
                if(!visited.count(neighbor)) {
                    visited.emplace(neighbor);
                    q.emplace(neighbor);
                }
            }
            // end of level
            if(level_nodes == 0) {
                if(q.empty())
                    break;
                level_nodes = q.size();
                ++level;
            }
        }
        return level;
    }
    
    int amountOfTime(TreeNode* root, int start) {
        // <node, [Neighboring nodes]
        unordered_map<int, vector<int>> graph;
        // create a graph using tree traversal
        postorder(root, graph);
        
        return bfs(start, graph);
    }
};
