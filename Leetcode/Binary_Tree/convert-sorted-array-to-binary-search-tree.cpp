/*
    https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
    
    TC: O(n)
    SC: O(logn)
    
    Height balanced BST requires 2 things:
    1. Ensure BST property is satisfied
    2. To keep the height balanced, ensure that nodes on left and right are almost equally divided
    
    So for range [low, high], we pick the mid element as the node, this leaves
    [low, mid-1] and [mid+1, high] no. of elements on both sides.
    And since we pick the middle element, the no. of elements for left and right sides are almost same,
    helping to keep the tree balanced.
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
    TreeNode* createBst(int low, int high, vector<int>& nums) {
        if(low > high)
            return nullptr;
        
        int mid = low + (high - low) / 2;
        TreeNode* node = new TreeNode(nums[mid]);
        
        node->left = createBst(low, mid-1, nums);
        node->right = createBst(mid+1, high, nums);
        
        return node;
    }
    
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return createBst(0, nums.size()-1, nums);
    }
};
