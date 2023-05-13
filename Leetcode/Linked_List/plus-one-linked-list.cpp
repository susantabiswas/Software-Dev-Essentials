/*
    https://leetcode.com/problems/plus-one-linked-list/
    
    TC: O(N)
    SC: O(1)
    
    Idea is to reverse the list so that the LSB is at the front.
    Then add the carry to each digit starting LSB till the carry is still
    left.
    Finally reverse the list back.
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
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        
        while(head) {
            ListNode* nxtptr = head->next;
            head->next = prev;
            prev = head;
            head = nxtptr;
        }    
        return prev;
    }
    
    ListNode* plusOne(ListNode* head) {
        // Reverese the list to get the digits from LSB to MSB
        ListNode* rev = reverseList(head);
        
        int carry = 1;
        ListNode* curr = rev, *prev = nullptr;
        
        while(curr && carry) {
            // add the carry and extract the carry 
            curr->val += carry;
            carry = curr->val / 10;
            curr->val %= 10;
            
            prev = curr;
            curr = curr->next;
        }
        
        // If carry is still left, add that
        if(carry)
            prev->next = new ListNode(carry);
        
        return reverseList(rev);
    }
};
