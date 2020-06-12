/*
    https://leetcode.com/problems/reorder-list/
    
    Reverse the second half of the list, 
    then we start merging them in the order given.
    
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
    // Reverses a linked list
    // TC: O(N)
    ListNode* reverseList(ListNode* head) {
        ListNode *nextptr = nullptr, *prev = nullptr;
        while(head) {
            nextptr = head->next;
            head->next = prev;
            prev = head;
            head = nextptr;
        }
        return prev;
    }
    
    // TC: O(N)
    void reorderList(ListNode* head) {
        if(!head || !head->next)
            return;
        
        // We use a dummy head to make head operations easier
        ListNode *dummy_head = new ListNode(-1), *tail = dummy_head,
            *nextptr = nullptr;
        
        // traverse till the mid point and reverse the second half
        // Even num of nodes: N/2 , 1-based index
        ListNode *slow = head, *fast = head, *prev = nullptr;
        while(slow && fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // end the first half
        if(prev)
            prev->next = nullptr;
        // head of reversed second half list
        ListNode *rev_head = reverseList(slow);
        
        // merge the list
        while(head && rev_head) {
            nextptr = head->next;
            // add two nodes from 1st and 2nd half
            tail->next = head;
            head->next = rev_head;
            tail = rev_head;
            
            head = nextptr;
            rev_head = rev_head->next;
        }
        
        // in case of odd no. of elements, 2nd list will have 1 more element
        tail->next = rev_head;
        
        // delete the dummy head
        head = dummy_head->next;
        delete dummy_head;
    }
};
