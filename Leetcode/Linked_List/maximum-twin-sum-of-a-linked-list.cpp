/*
    https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/
    
    TC: O(n)
    SC: O(1)
    
    Idea is to simply reverse the 2nd half of list. Then use 2 pointers, one pointing
    to the first node of 1st half of list and the second pointing to the 1st node of second half.
    
    Now start the traversal and at each time track the max twin sum observed.
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
    ListNode* reverseList(ListNode* head) {
        ListNode* nxt_ptr = nullptr, *curr = head;
        ListNode* prev = nullptr;
        
        while(curr) {
            nxt_ptr = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt_ptr;
        }
        return prev;
    }
    
    int pairSum(ListNode* head) {
        int max_sum = 0;
        
        // find the mid point
        ListNode* curr = head;
        ListNode* slow = head, *fast = head;
        ListNode* prev = nullptr;
        
        // after this, the slow will be at ceil(n/2) and prev at floor(n/2)
        while(slow && fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // split the list
        prev->next = nullptr;
        
        // reverse the linked list from mid point
        ListNode* rev_head = reverseList(slow);
        
        // traverse till half the list
        // while tracking the max twin sum
        ListNode* first = head, *second = rev_head;
        while(first) {
            max_sum = max(max_sum, first->val + second->val);
            first = first->next;
            second = second->next;
        }
        
        // NOTE: revert the changes made to the list if the question demands 
        return max_sum;
    }
};
