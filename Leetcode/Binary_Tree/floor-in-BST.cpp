/*
    https://www.codingninjas.com/studio/problems/floor-from-bst_920457

    Floor in BST 

    TC: O(h + n)
    We go till the depth and then do the traversal till we find the
    a > X
*/
#include <bits/stdc++.h> 
/************************************************************

    Following is the TreeNode class structure

    template <typename T>
    class TreeNode {
       public:
        T val;
        TreeNode<T> *left;
        TreeNode<T> *right;

        TreeNode(T val) {
            this->val = val;
            left = NULL;
            right = NULL;
        }
    };

************************************************************/
int floorInBST(TreeNode<int> * root, int X)
{
    stack<TreeNode<int>*> s;

    TreeNode<int> * curr = root, *prev = nullptr;
    
    while(curr || !s.empty()) {
        while(curr) {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        if(curr->val > X)
            break;
        prev = curr;

        curr = curr->right;
    }

    return prev->val;
}
