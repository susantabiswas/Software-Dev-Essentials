/*
    https://leetcode.com/problems/linked-list-in-binary-tree/submissions/
    
    Idea is do BFS of tree and once we get the a node which has the same value as that
    of the list head, then we start DFS of tree from that node and list head to check if that
    path exists from that node.
    
*/
class Solution {
public:
    bool checkPath(ListNode* head, TreeNode* root) {
        // if the list has ended
        if(!head)
            return true;
        // if the list hasnt ended but tree has
        if(!root)
            return false;
        
        return head->val == root->val && (checkPath(head->next, root->left) ||
                                         checkPath(head->next, root->right));
    }
    
    // TC: O(M * min(M, N)), M: size of linked list, N: No. of nodes in tree
    bool isSubPath(ListNode* head, TreeNode* root) {
        queue<TreeNode*> q;
        q.emplace(root);
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            
            // check if the current node match the list head
            if(curr->val == head->val && checkPath(head, curr))
                return true;
            
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
        }
        
        return false;
    }
};
