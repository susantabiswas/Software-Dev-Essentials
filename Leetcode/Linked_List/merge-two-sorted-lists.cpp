/*
    https://leetcode.com/problems/merge-two-sorted-lists/submissions/
    
    Idea is to do a simple traversal starting with the heads of two.
    While we have nodes from both the lists, we compare and add the smaller value
    node and continue.
    
    TC: O(N + M), SC: O(1)
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // We use a dummy head node to make handling the head
        // node easier
        ListNode *dummy_head = new ListNode(-1), *tail = dummy_head;
        
        while(l1 && l2) {
            if(l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            }
            else {
                tail->next = l2;
                l2 = l2->next;
            }
            // add the node
            tail = tail->next;
        }
        
        // add any remaining nodes 
        ListNode *temp = l1 ? l1 : l2;
        while(temp) {
            tail->next = temp;
            temp = temp->next;
            tail = tail->next;
        }
        
        // delete the dummy head
        ListNode *head = dummy_head->next;
        delete dummy_head;
        return head;
    }
};
