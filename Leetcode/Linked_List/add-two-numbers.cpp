/*
    https://leetcode.com/problems/add-two-numbers/
    TC: O(L), SC: O(L), L = max(m,n)
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int val = 0, carry = 0;
        // dummy head
        ListNode* dummy = new ListNode(-1);
        ListNode* last = dummy;
        
        // add the digits from LSB
        while(l1 && l2) {
            val = l1->val + l2->val + carry;
            ListNode* node = new ListNode(val % 10);
            // add the current position node to the result
            last->next = node;
            last = last->next;
            
            // update carry for next position
            carry = val / 10;
            
            l1 = l1->next, l2 = l2->next;
        }
        
        // if any of the numbers still exists, add it the result
        ListNode* iter = l1 == nullptr ? l2 : l1;
        
        while(iter) {
            val = carry + iter->val;
            ListNode* node = new ListNode(val % 10);
            carry = val / 10;
            // add the current position node to the result
            last->next = node;
            last = last->next;
            // goto next node
            iter = iter->next;
        }
        // If carry exists, make it MSB
        if(carry)
            last->next = new ListNode(carry);
        
        return dummy->next;
    }
};
