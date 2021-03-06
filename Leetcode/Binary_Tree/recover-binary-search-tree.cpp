/*
    https://leetcode.com/problems/recover-binary-search-tree/
    
    Inorder traversal of BST gives the sequence of numbers in non-decreasing order.
    The problem then can be thought of as finding the pair of swapped numbers
    in a sorted sequence of numbers.
    To solve this we need to look for the pairs which follows A > B.
    If there are two such pairs, first number of 1st pair and the second
    number of the 2nd pair are the swapped numbers. If only pair is found 
    then the 1st pair of numbers were swapped.
    The logic behind is that in a sorted sequence of numbers A..... B.....C...D,
    if we swap two numbers B and C, then the greater number will go to B's pos and
    it will still look valid during traversal, so we need to keep track of both the
    numbers of the first pair. B being a smaller number than C when is swapped, makes
    B look smaller during traversal and we can just track the smaller number found
    in the second time.
    
    Finally swap the found numbers.
    TC: O(N)
    SC: O(1)
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
    void fixTree(TreeNode *root, TreeNode* &prev,
                TreeNode* &first, TreeNode* &second) {
        if(root) {
            fixTree(root->left, prev, first, second);
            // pair found not in non-decreasing order
            if(prev && prev->val > root->val) {
                // first pair of numbers which are not in 
                // non-decreasing order
                if(!first) {
                    first = prev;
                    second = root;
                }
                else
                    second = root;
            }
            
            prev = root;
            fixTree(root->right, prev, first, second);
        }
    }
    
    void recoverTree(TreeNode* root) {
        TreeNode *first = nullptr, 
            *second = nullptr, *prev = nullptr;
        
        fixTree(root, prev, first, second);
        // swap the node values
        swap(first->val, second->val);
    }
};
