/*
    https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
    
    TC: O(N)
    SC: O(N)
    
    Idea is simple, post order processes right, left and curr. This means the last element is the
    root, then the next is the right,then next is left and so on.
    Also inorder processes in left, curr and right order. So for a postorder node, if we can find
    the position in the order array, then we will know what lies on the left and right 
    side of the node.
    
    Now the next problem is to do this efficiently. Searching for a node in the inorder
    array is O(n), so we precompute this by saving the position of each element in a hash table.
    
    Then we do the above concept to solve the problem.
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
    TreeNode* createTree(int& curr, int left, int right, vector<int>& inorder, vector<int>& postorder, unordered_map<int, int>& pos) {
        if(left > right)
            return nullptr;
        
        TreeNode* node = new TreeNode(postorder[curr]);
        
        // find the position in inorder and recurse for the left and right
        // side of index
        int idx = pos[postorder[curr]];
        --curr;
        
        node->right = createTree(curr, idx+1, right, inorder, postorder, pos);
        node->left = createTree(curr, left, idx-1, inorder, postorder, pos);
        
        return node;
    }
    
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = postorder.size() - 1;
        // map the position with value
        unordered_map<int, int> pos;
        
        for(int i = 0; i <= n; i++)
            pos[inorder[i]] = i;
        
        return createTree(n, 0, n, inorder, postorder, pos);
    }
};
