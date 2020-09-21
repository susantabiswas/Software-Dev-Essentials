/*
    https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/submissions/
    
    Idea is that for each of the subtrees, we check if the subtree with either of left or right
    node as parent if multiplied with the sum of all remaining nodes can give us the max product.
    To get the sum of remaining nodes at any point, we need to first compute the total sum of nodes
    of tree.
    After that we do a postorder traversal where each call returns the sum of the subtree starting there.
    So to get sum of remaining nodes at any point, total_sum - subtree_sum, check product cmb for 
    both left and right subtrees.
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
private:
    const int MOD = pow(10, 9) + 7;
public:
    // Returns the total sum of all the nodes 
    long long preOrder(TreeNode *root) {
        if(root) {
            return root->val + preOrder(root->left) 
                + preOrder(root->right);
        }    
        return 0;
    }
    
    long long maxSplit(TreeNode *root, long long prev_sum,
                 long long &max_prod) {
        if(!root)
            return 0;
        
        // get the total sum of nodes in left and right subtrees
        long long left = maxSplit(root->left, prev_sum, max_prod);
        long long right = maxSplit(root->right, prev_sum, max_prod);
        // sum of all the nodes excluding the current child subtrees
        long long remaining_sum = prev_sum  - left - right;
        // check the product of subtree sum when left and right 
        // edges are removed, one at a time
        long long cmb1 = left * (remaining_sum + right);
        long long cmb2 = right * (remaining_sum + left);
        max_prod = max({max_prod, cmb1, cmb2});
        
        return root->val + (left + right);
    }
    
    int maxProduct(TreeNode* root) {
        long long max_prod = 0;
        // find the total sum of all the nodes
        long long sum = preOrder(root);
        
        maxSplit(root, sum, max_prod);
        return max_prod % MOD;
    }
};
