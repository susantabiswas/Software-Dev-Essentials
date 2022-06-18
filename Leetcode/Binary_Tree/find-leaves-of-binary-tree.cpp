/*
    https://leetcode.com/problems/find-leaves-of-binary-tree/
    
    To find the leaf level for a node, we need to track the height of node wrt
    to the leaf in its subtree. For a node, its leaf level is the 
    max_leaf_leaf_height(left subtree, right subtree). This is because the bigger subtree leaf 
    level height tells us that that subtree will have more nodes in the path than the other subtree, 
    and only when these extra nodes are accounted for, the current node will become a leaf node. 
    
    TC: O(N)
    SC: O(N)
*/
/*
    Given the root of a binary tree, collect a tree's nodes as if you were doing this:

    Collect all the leaf nodes.
    Remove all the leaf nodes.
    Repeat until the tree is empty.
    
    Input: root = [1,2,3,4,5]
    Output: [[4,5,3],[2],[1]]
    Explanation:
    [[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers since per each level it does not matter the order on which elements are returned.
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
    // DFS Solution 1
    void dfs1(TreeNode* root, int& leaf_level,
             unordered_map<int, vector<int>>& leaf_levels) {
        if(!root)
            return;
        // Tracks the leaf height from left and right subtree
        int left_leaf_height = 0, right_leaf_height = 0;
        dfs1(root->left, left_leaf_height, leaf_levels);
        dfs1(root->right, right_leaf_height, leaf_levels);
        
        // add the current node to appropriate leaf height level
        int leaf_height_level = max(left_leaf_height, right_leaf_height);
        leaf_levels[leaf_height_level].emplace_back(root->val);
        leaf_level = leaf_height_level + 1;
    }
    
    vector<vector<int>> dfsSol1(TreeNode* root) {
        // <height, [nodes]>
        unordered_map<int, vector<int>> leaf_levels;
        int leaf_level = 0;
        
        dfs1(root, leaf_level, leaf_levels);
        
        // Add the per level leaf nodes
        vector<vector<int>> order(leaf_levels.size());
        for(int level = 0; level < leaf_levels.size(); level++)  
             order[level] = move(leaf_levels[level]);
        
        return order;
    }
    
    // DFS Solution 2
    int dfs2(TreeNode* root, vector<vector<int>>& order) {
        if(!root)
            return -1;
        
        // Tracks the leaf height from left and right subtree
        int leaf_level_height = 1 + max(dfs2(root->left, order),
                                    dfs2(root->right, order));
        
        if(order.size() <= leaf_level_height)
            order.push_back({});
        // add the current node to appropriate leaf height level
        order[leaf_level_height].emplace_back(root->val);
        
        return leaf_level_height;
    }
    
    vector<vector<int>> dfsSol2(TreeNode* root) {
        vector<vector<int>> order;
        dfs2(root, order);
        return order;
    }
    
    vector<vector<int>> findLeaves(TreeNode* root) {
        // return dfsSol1(root);
        return dfsSol2(root);
    }
};
