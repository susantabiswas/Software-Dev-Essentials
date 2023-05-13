/*
    https://leetcode.com/problems/reverse-linked-list-ii/
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
    
    // For reversing a linked list
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = nullptr, *nextptr = nullptr;
        
        while(head) {
            // save the next node and make the next of 
            // current nod ethe previous node
            nextptr = head->next;
            head->next = prev;
            prev = head;
            head = nextptr;
        }
        
        return prev;
    }
    
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // if the list to reverse has only 1 node
        if(m == n)
            return head;
        
        // Idea is to first find the mth node, then from there cover n - m distance
        // and reach nth node, then separate the m-->...-->n list, reverse it and put it back
        
        // Case: when m = 1, head node changes, to handle it easily we use a dummy head
        ListNode *dummy_head = new ListNode(-1);
        ListNode *prev = dummy_head, *curr = head;
        int idx = 0;
        
        dummy_head->next = head;
        
        // find the starting node, loop ends with curr being the mth node
        while(curr && idx < m-1) {
            ++idx;
            prev = curr;
            curr = curr->next;    
        }
        
        // now cover n-m distance
        int dist = n - m;
        ListNode *before_mth = prev, *mth_node = curr;
        idx = 0;
        // traverse till nth node is reached, loop ends with curr being nth
        while(curr && idx < dist) {
            ++idx;
            prev = curr;
            curr = curr->next;
        }
        
        ListNode *after_nth = curr->next;
        // separate the list and reverse it
        curr->next = nullptr;
        before_mth->next = reverseList(mth_node);
        // connect with remaining list
        mth_node->next = after_nth;
        
        // delete dummy head
        head = dummy_head->next;
        delete dummy_head;
        
        return head;
    }
};
