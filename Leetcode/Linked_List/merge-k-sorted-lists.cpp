/*
    https://leetcode.com/problems/merge-k-sorted-lists/submissions/
    
    The idea is to merge the lists in tournament tree order to mnimize the 
    number of merge operations.
    
    TC: O(NlogK), N: length of longest list
        there will be logK merge operations and a worst case list of size N will be merged
        = 2T(k/2) + N
        = N * logK
    SC: O(1)
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
    // Merges two lists into one
    ListNode* mergeList(ListNode* first, ListNode* second) {
        // dummy head to make handling head operations easier
        ListNode *dummy_head = new ListNode(-1), *tail = dummy_head;
        
        while(first && second) {
            if(first->val < second->val) {
                tail->next = first;
                first = first->next;
            }
            else {
                tail->next = second;
                second = second->next;
            }
            
            // add the node to final list
            tail = tail->next;
        }
        
        // add any remaining nodes
        ListNode *t = first ? first : second;
        while(t) {
            tail->next = t;
            tail = tail->next;
            t = t->next;
        }
        
        ListNode *head = dummy_head->next;
        delete dummy_head;
        
        return head;
    }
    
    
    // Merges the lists recursively in a tournament tree manner
    ListNode* mergeLists(int start, int end, vector<ListNode*>& lists) {
        // base case
        if(start == end) {
            return lists[start];
        }
        if(start < end) {
            int mid = start + (end - start) / 2;
            ListNode *left = mergeLists(start, mid, lists);
            ListNode *right = mergeLists(mid + 1, end, lists);
            ListNode *merged_head = mergeList(left, right);
            return merged_head;
        }
        return nullptr;
    }
    
    // Driver 
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return mergeLists(0, lists.size() - 1, lists);
    }
};
