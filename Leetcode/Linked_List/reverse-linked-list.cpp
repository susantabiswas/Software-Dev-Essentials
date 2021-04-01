/*
    https://leetcode.com/problems/reverse-linked-list/solution/
    
    Most important thing to handle is the addr of next node while traversing.
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
    
    // Recursive sol, TC: O(N), SC: O(N)
    ListNode *revList(ListNode *head) {
        if(!head || !head->next)
            return head;
        // save the next node ptr, this can be used to
        // reverse the current link
        ListNode *nextptr = head->next;
        ListNode *rev_head = revList(nextptr);
        // reverse the link
        nextptr->next = head;
        head->next = nullptr;
        return rev_head;
    }
    
    // Iterative sol, TC: O(N), SC: O(1)
    ListNode *revListIter(ListNode *head) {
        ListNode *nextptr = nullptr, *prev = nullptr;
        
        while(head) {
            nextptr = head->next;
            // make the current node point to its previous
            head->next = prev;
            prev = head; 
            head = nextptr; // go to next node
        }
        return prev;
    }
    
    ListNode* reverseList(ListNode* head) {
//         return revList(head);
        return revListIter(head);
    }
};
