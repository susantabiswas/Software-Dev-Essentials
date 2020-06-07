/*
    https://leetcode.com/problems/swap-nodes-in-pairs/
    
    Idea is to take 2 ndoes at a time and swap them, then make the
    2st node connected to the 3rd node if there and continue with the 3rd node.
    TC: O(N), SC:O(1)
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
    ListNode* swapPairs(ListNode* head) {
        // We use a dummy head node to make handling head operations simpler
        ListNode *dummy = new ListNode(-1), *tail = dummy;
        // add the dummy node to list
        tail->next = head;
        
        while(head && head->next) {
            ListNode *nextptr = head->next->next;
            // swap the adjacent nodes
            // 2nd node comes to 1st pos 
            tail->next = head->next;
            // connecting 2nd node to 1st node
            (head->next)->next = head;
            // make the 1st node connected to next node on list
            tail = head;
            tail->next = nextptr;
            head = nextptr;
        }
        
        head = dummy->next;
        delete dummy;
        return head;
    }
};
