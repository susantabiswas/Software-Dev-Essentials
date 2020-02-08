/*
    https://leetcode.com/problems/odd-even-linked-list/
    TC: O(N)
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
    ListNode* oddEvenList(ListNode* head) {
        // dummy head nodes are odd and even lists
        ListNode *odd_head = new ListNode(-1), *even_head = new ListNode(-1);
        // tail nodes for odd and even lists
        ListNode *odd_tail = odd_head, *even_tail = even_head;
        
        int pos = 0;
        // temp ptr foor traversal
        ListNode* iter = head;
        while(iter) {
            ++pos;
            // add the odd node
            if(pos % 2 != 0) {
                odd_tail->next = iter;
                odd_tail = odd_tail->next;
            }
            // add tthe even node
            else {
                even_tail->next = iter;
                even_tail = even_tail->next;
            }
            // go to next node
            iter = iter->next;
        }
        // terminate the individual lists
        odd_tail->next = nullptr, even_tail->next = nullptr;
        // add the odd and even lists together
        odd_tail->next = even_head->next;
        return odd_head->next;
     }
};
