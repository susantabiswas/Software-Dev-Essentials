/*
    https://leetcode.com/problems/split-linked-list-in-parts/submissions/
    
    Max equal nodes per group: N/k
    remaining nodes, that needs to be given in sequential manner starting from beginning: N % k
    Idea is to traverse the required no. of nodes for each group, end the sublist and 
    add to the group and continue.
    
    TC: O(N), SC: O(1)
*/


class Solution {
public:
    // Finds no. of nodes in list
    // TC: O(N)
    int nodeCount(ListNode* head) {
        int c = 0;
        while(head) {
            ++c;
            head = head->next;
        }
        return c;
    }
    
    // TC: O(N)
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        // N/k gives max equal no. of nodes per block. In order to keep the
        // max diff 1, we add 1 from each of the remaining N % k elements
        // to the groups from start
        const int N = nodeCount(root);
        
        int elements_per_group = N / k;
        int extra_nodes = N % k;
        
        vector<ListNode*> result(k);
        
        ListNode *curr = root;
        
        for(int i = 0; i < k; i++) {
            int remaining = elements_per_group;
            // if any extra nodes needs to added
            if(extra_nodes > 0) {
                remaining += 1;
                --extra_nodes;
            }

            result[i] = curr;
            ListNode *prev = nullptr;
            // traverse the no. of nodes that will be assigned
            while(remaining--) {
                prev = curr;
                curr = curr->next;
            }
            // end the list
            if(prev)
                prev->next = nullptr;
        }    
        
        return result;
    }
};
