/*
    https://leetcode.com/problems/reverse-nodes-in-k-group/
    
    Idea is to traverse the list with k groups in mind. For every group found, we
    separate and reverse the group and insert it back in the following order:
    prev_node--> reversed --->next_node
    
    TC: O(N), SC: O(1)
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
    // for reversing a linked list
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = nullptr, *nextptr = nullptr;
        
        while(head) {
            nextptr = head->next;
            // make the current node point to previous
            head->next = prev;
            // current node becomes previous now
            prev = head;
            head = nextptr;
        }
        return prev;
    }
    
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        
            
        // dummy head node to make head related ops easier
        ListNode *dummy = new ListNode(-1), *tail = dummy;
        ListNode *nextptr = nullptr;
        tail->next = head;
        
        while(head) {
            // traverse k nodes, after loop end
            // it will be on kth node
            int i = 1;
            // this node will be the last node once reversed
            ListNode *first_node = head;
            while(head->next && i < k) {
                head = head->next;
                ++i;
            }
            nextptr = head->next;
            // end the k sized list
            head->next = nullptr;
            // reverse the nodes only if there are k nodes
            if(i == k) {
                tail->next = reverseList(first_node);
                first_node->next = nextptr;
                // update tail node
                tail = first_node;
            }
            head = nextptr;
        }
        
        head = dummy->next;
        delete dummy;
        
        return head;
    }
};
