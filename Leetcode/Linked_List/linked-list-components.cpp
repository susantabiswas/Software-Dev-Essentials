/*
    https://leetcode.com/problems/linked-list-components/
    TC: O(N)
    SC: O(m), m: size of G
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
    int numComponents(ListNode* head, vector<int>& G) {
        // set of all the subset elements which are considered unvisited initially
        unordered_set<int> unvisited(begin(G), end(G));
        int conn_components = 0;
        
        ListNode* iter = head;
        // As we traverse through the list, we find all the nodes connected in G 
        // from the current node and remove them unvisited set
        while(iter) {
            // check if current node is in G or not
            if(unvisited.find(iter->val) != unvisited.end()) {
                ++conn_components;
                // now find all the nodes connected via current node
                // and remove them from unvisited set
                while(iter && unvisited.find(iter->val) != unvisited.end()) {
                    // remove the current from list of unvisited
                    unvisited.erase(iter->val);
                    iter = iter->next;
                }
            }
            if(iter)
                iter = iter->next;
        }
        return conn_components;
    }
};
