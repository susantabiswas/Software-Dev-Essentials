/*
    https://leetcode.com/problems/delete-node-in-a-linked-list/
    
    We make the current node value set to the next node and then delete the 
    next node.
    
    TC: O(1), SC: O(1) 
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        // store the next node to delete
        ListNode *temp = node->next;
        node->val = node->next->val;
        node->next = node->next->next;
        // delete the node
        delete temp;
    }
};
