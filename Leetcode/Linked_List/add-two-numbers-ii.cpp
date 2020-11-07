/*
    https://leetcode.com/problems/add-two-numbers-ii/submissions/

    
    TC: O(N)
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
    ListNode *reverseList(ListNode *head) {
        ListNode *prev = nullptr, *temp = head,
            *nextptr = nullptr;
        
        while(temp) {
            nextptr = temp->next;
            temp->next = prev;
            prev = temp;
            temp = nextptr;
        }
        return prev;    
    }
    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // reverse the lists to make it LSB -> MSB
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        
        int carry = 0;
        ListNode *num1 = l1, *num2 = l2;
        // dummy head
        ListNode *dummy = new ListNode(-1), *tail = dummy; 
        
        while(num1 && num2) {
            // add the current sum digit
            int curr = carry + num1->val + num2->val;
            ListNode *curr_digit = new ListNode(curr % 10);
            carry = curr / 10;
            
            tail->next = curr_digit;
            tail = tail->next;
            
            // go to the next digit
            num1 = num1->next;
            num2 = num2->next;
        }
        
        // add remaining digits
        while(num1) {
            int curr = num1->val + carry;
            tail->next = new ListNode(curr % 10);
            carry = curr / 10;
            // iterate forward
            num1 = num1->next;
            tail = tail->next;
        }
        
        while(num2) {
            int curr = num2->val + carry;
            tail->next = new ListNode(curr % 10);
            carry = curr / 10;
            // iterate forward
            num2 = num2->next;
            tail = tail->next;
        }
        
        // check if carry digit is there
        if(carry)
            tail->next = new ListNode(carry);
        
        // delete the dummy head to avoid memory leak
        ListNode *temp = dummy;
        dummy = dummy->next;
        delete temp;
        // since the current list is in LSB->MSB, we reverse it again
        return reverseList(dummy);
    }
};
