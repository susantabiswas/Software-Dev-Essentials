/*
    https://leetcode.com/problems/sort-list/
    
    In order to get O(nlogn), we use merge sort on linked list.
    Unlike an array, where access to mid point is O(1), here is O(N) and is 
    not direct.
    
    T(n) = T(n/2) + O(N), O(N): for finding mid point and merging
        = O(nlogn)
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
    // Finds the middle node, it gives ceil(N/2), 1-indexed
    // TC: O(N)
    ListNode* findMiddle(ListNode* head) {
        // We use tortoise-hare algo
        ListNode *slow = head, *fast = head, *prev = nullptr;
        while(slow && fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        // fast becomes NULL when there are even no. of nodes
        return fast ? slow : prev;
    }
    
    // Merges two linked lists
    // TC: O(n + m)
    ListNode* mergeLists(ListNode* h1, ListNode* h2) {
        // We use a dummy node, makes head operations easier
        ListNode *dummy_head = new ListNode(-1), *tail = dummy_head;
        
        // traverse both the lists and add the smaller one,
        // we stop traversing once a list finishes
        while(h1 && h2) {
            if(h1->val < h2->val) {
                tail->next = h1;
                h1 = h1->next;
            }    
            else {
                tail->next = h2;
                h2 = h2->next;
            }
            tail = tail->next;
        }
        
        // check if any list is remaining
        ListNode *curr = h1 ? h1 : h2;
        while(curr) {
            tail->next = curr;
            tail = tail->next;
            curr = curr->next;    
        }
        
        ListNode *head = dummy_head->next;
        delete dummy_head;
        
        return head;
    }
    
    // Merge sort for linked list
    ListNode* mergeSortList(ListNode* head) {
        // 0 or 1 node
        if(!head || !head->next)
            return head;
        // find the middle node
        ListNode * mid = findMiddle(head);
        
        // split the list in two parts
        ListNode *right_head = mid->next;
        // end the left list
        mid->next = nullptr;
        // recurse for left and right side
        ListNode *left = mergeSortList(head);
        ListNode *right = mergeSortList(right_head);
        // merge the two lists
        ListNode *merged_head = mergeLists(left, right);
        
        return merged_head;
    }
    
    // TC: O(NlogN)
    ListNode* sortList(ListNode* head) {
        return mergeSortList(head);
    }
};
