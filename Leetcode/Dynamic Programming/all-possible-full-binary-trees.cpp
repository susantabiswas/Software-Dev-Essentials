/*
    https://leetcode.com/problems/all-possible-full-binary-trees/
    
    Things to note:
    1. It is not possible to create a full binary tree with even no. of total nodes.
    This is because, a root node would take 1 count and that leaves n-1 nodes which if n is even
    would be odd. With odd no. of nodes it is not possible to fulfil 0 or 2 child node criteria.
    
    2. If we know about the trees that can be created for say n = 3, we can use that for n = 5.
    For n = 5:
                0
              /   \
        n = 1,3    n = 1,3
    We can simply attach the tree for n = 3 and n = 1 depending on n
    
    So similar too Unique BST II problem, we find all possible trees for smaller n and then using those trees
    slowly build the larger tree.
    Each time we recurse for both left and right subtrees.
    
    TC : O(Summation(Catalan(k)) from k < N/2) <= O(2^N)
        
        Since we only compute for odd numbers,
        for N = 2k + 1
    SC: O(2^N)
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
    vector<TreeNode*> createTree(int n, unordered_map<int, vector<TreeNode*> >& dp) {
        // base case: invalid n
        if(n <= 0 || n % 2 == 0)
            return {};
        
        // current value is not cached
        if(dp.count(n) == 0) {
            vector<TreeNode*> trees;
        
            // base case: Single node
            if(n == 1)
                return { new TreeNode(0) };

            // For the given n, we fix the root and find out possible
            // trees for the left and right subtrees
            for(int i = 1; i < n; i += 2) {
                vector<TreeNode*> left_subtrees = createTree(i, dp);
                vector<TreeNode*> right_subtrees = createTree(n - 1 - i, dp); // 1 for the root

                // Now put each possible left and right subtree combination
                for(int left = 0; left < left_subtrees.size(); left++)
                    for(int right = 0; right < right_subtrees.size(); right++) {
                        // create the current root node and attach the left and right subtrees
                        TreeNode* root = new TreeNode(0);
                        root->left = left_subtrees[left];
                        root->right = right_subtrees[right];

                        trees.emplace_back(root);
                    }
            }
            dp[n] = trees;
        }
        return dp[n];
    }
    
    vector<TreeNode*> allPossibleFBT(int n) {
        // <node_count, [Root of all possible full binary trees]>
        unordered_map<int, vector<TreeNode*> > dp;
        return createTree(n, dp);
    }
};
