/*
    https://www.codingninjas.com/studio/problems/ceil-from-bst_920464

     Ceil from BST 
    TC: O(h + n)

*/

#include <bits/stdc++.h> 
/************************************************************

    Following is the TreeNode class structure:

    class BinaryTreeNode {
    public:
        T data;
        BinaryTreeNode<T> *left;
        BinaryTreeNode<T> *right;
        
        BinaryTreeNode(T data) {
            this->data = data;
            left = NULL;
            right = NULL;
        }
        
        ~BinaryTreeNode() {
            if (left) {
              delete left;
            }
            if (right) {
              delete right;
            }
        }
    };

************************************************************/

int findCeil(BinaryTreeNode<int> *node, int x){
    // Write your code here.
    stack<BinaryTreeNode<int>*> s;

    BinaryTreeNode<int>* curr = node, *prev = nullptr;

    while(curr || !s.empty()) {
        while(curr) {
            s.push(curr);
            curr = curr->right;
        }

        curr = s.top();
        s.pop();

        if(curr->data < x)
            break;

        prev = curr;

        curr = curr->left;
    }

    return prev ? prev->data : -1;
}
