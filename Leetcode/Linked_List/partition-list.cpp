/*
    https://leetcode.com/problems/partition-list/
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
    ListNode* partition(ListNode* head, int x) {
        // We make two separate lists:
        // List 1: values < x
        // List 2: value >= x
        // Finally add the two lists
        // Lis1 --> List2
        // We use dummy head nodes for both the lists to make insertion operations simpler
        ListNode *smaller_head = new ListNode(-1), *smaller_tail = smaller_head,
                *greater_head = new ListNode(-1), *greater_tail = greater_head;
        
        while(head) {
            if(head->val < x) {
                smaller_tail->next = head;
                smaller_tail = smaller_tail->next;
            }
            else {
                greater_tail->next = head;
                greater_tail = greater_tail->next;
            }
                
            // traverse to next node
            head = head->next;
        }
        // end both the lists
        smaller_tail->next = nullptr;
        greater_tail->next = nullptr;
        
        // head node of final list
        ListNode *partition_head = nullptr;
        
        // connect the two lists
        smaller_tail->next = greater_head->next;
        partition_head = smaller_head->next;
        // delete the dummy heads
        delete smaller_head, greater_head;
        
        return partition_head;
    }
};
