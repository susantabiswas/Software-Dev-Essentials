/*
    654. Maximum Binary Tree
    https://leetcode.com/problems/maximum-binary-tree/
    
    For the given array range, find the max element index and create root with that.
    Then recurse for the left and right side remaining array for creating left and right 
    subtrees.
    
    TC: O(n^2)
    
    Solution using stack:
    We use a stack for keeping track of largest elements in decreasing order.
    So all the bigger elements on the left till current array element will be in 
    stack and they will become parents before current array element if it is smaller than them,
    meaning the element just before it in stack is its parent. It is going to be the left child of stack top element for now, 
    this might change if there exists any element greater than current later on. If the stack elements are smaller than current, 
    then they are popped and the last to be popped is the one which is going to be the left child of current.  
    
    Scan from left to right :
        create node with current number
        pop stack elements while smaller:
            make each popped element as right child of curr, so 
            finally the element just smaller will be the right child
            
        if stack not empty:
            make current element left child of stack top, this can change if there 
            is a bigger element ahead
            
        push curr to stack
        
    pop all elements till we get the first stack element
    return first element, this is the largest number and root
    
    Tc: O(n)
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
    
    // Quadratic solution
    TreeNode* constructTree(vector<int>& nums, int l, int h) {
        if(l > h) 
            return nullptr;

        // find the max
        int max_idx = -1;
        int max_el = numeric_limits<int> :: min();
        for(int i = l; i <= h; i++) {
            if(nums[i] > max_el) {
                max_el = nums[i];
                max_idx = i;
            }
        }

        TreeNode* root = new TreeNode(nums[max_idx]);
        // recurse for left and right subtrees
        root->left = constructTree(nums, l, max_idx-1);
        root->right = constructTree(nums, max_idx+1, h);

        return root;
    }
    
    // O(n) solution
    TreeNode* constructTreeStack(vector<int>& nums) {
        stack<TreeNode*> s;
        
        for(int num: nums) {
            TreeNode* curr = new TreeNode(num);
            // Keep popping till there is a bigger element 
            while(!s.empty() && s.top()->val < curr->val) {
                // set the popped element as right child for current
                curr->left = s.top();
                s.pop();
            }
            
            // if there is a bigger element on left side, make current its left child for now
            if(!s.empty())
                s.top()->right = curr;
            s.emplace(curr);
        }
        
        TreeNode* curr = nullptr;
        // root will be the largest element, which is the first stack element
        while(!s.empty()) {
            curr = s.top();
            s.pop();
        }
        return curr;
    }
    
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
       // TreeNode* root = constructTree(nums, 0, nums.size() - 1);
        TreeNode* root = constructTreeStack(nums);
        return root;
    }
};
