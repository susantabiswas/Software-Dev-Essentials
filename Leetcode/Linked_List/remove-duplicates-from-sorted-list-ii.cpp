/*
    https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/submissions/
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
    ListNode* deleteDuplicates(ListNode* head) {
        // dummy head 
        ListNode* dummy_head = new ListNode(0);
        ListNode *last = dummy_head, *temp = head;
        
        while(temp) {
            // starting current node traverse till all
            // the duplicates are covered, then if there are 
            // duplicates, then that node is not added to the list 
            int c = 1;
            while(temp->next && temp->val == temp->next->val)
                temp = temp->next, c += 1;
            if(c == 1) {
                last->next = temp;
                last = last->next;
            }
            temp = temp->next;
        }
        
        // delete the dummy head and return the resultant list
        head = dummy_head->next;
        last->next = nullptr;
        delete dummy_head;
        
        return head;
    }
};
