/*
    https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/submissions/
    
    Idea is to find out the distance of leaf nodes in left and right subtrees
    for each of the parent nodes. For a node 'i', if we know the distance of leaf nodes
    in its left and right from it, then we can just check if the sum of distance of the leaf nodes
    in left and right <= dist limit, that makes it a good pair.
    
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
    // TC: O(n * d * d), d: max distance limit, n: num of nodes
    vector<int> postOrder(TreeNode *root, int &distance,
                          int &good_leaves) {
        // dist(i): no. of leaf nodes with dist 'i' from current node
        vector<int> dist(distance + 1, 0);
        if(!root)
            return dist;
        
        // when current is a leaf node, its distance with its parent will be 1
        if(!root->left && !root->right) {
            dist[1] = 1;
            return dist;
        }
        
        // find the distance of leaf and right subtree leaf nodes
        auto left_dist = postOrder(root->left, distance, good_leaves);
        auto right_dist = postOrder(root->right, distance, good_leaves);
        
        // now check the distances between leaf nodes of leaf and right 
        // subtrees which are under limit
        for(int i = 0; i < left_dist.size(); i++)
            for(int j = 0; j < right_dist.size(); j++)
                if(i + j <= distance) {
                    good_leaves += (left_dist[i] * right_dist[j]);
                }
        // Update the distance for parent and include the current node
        for(int i = 1; i <= distance; i++) {
            // (i-1) distance becomes distance 'i' 
            dist[i] = left_dist[i-1] + right_dist[i-1];
        }
        
        return dist;
    }
    
    
    int countPairs(TreeNode* root, int distance) {
        int good_leaves = 0, curr_dist = -1;
        postOrder(root, distance, good_leaves);
        return good_leaves;
    }
};
