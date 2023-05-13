/*
    https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
    
        
    SOLUTION 1
        To get a height balanced tree from sorted elements, we make the middle element as the
        root and recurse its left and right sides for left and right subtrees respectively.

        Since we are not working with an array, we cant access a data element directly by its position
        and hence cant use a merge sort like logic directly. So we use tortoise-hare algo to find the middle 
        node of linked list, use that to split the list in two parts. The next node becomes the root node and 
        the node after that becomes the head of the second list.

        T(n) = T(n/2) + O(n)
            = O(nlogn)
        SC: O(logn), recursive stack
        
    SOLUTION 2
        The main time consuming part in above solution is finding the middle each time, we
        can actually reduce that part. The idea is to make the current head point to the middle element 
        in each recursive call with elements from [l:r]. This can be done by making the tree in inorder fashion
        and keep a reference to the list head across all the calls. Everytime we create a node, we traverse the
        node by 1 step.
        Eg: index range: [1:3] and list: 1->2->3, head=1
        When we reach 1([1:1]), we create 1, update head=2
        So when we go to the parent recursive call with limit[1:3], our head point to middle 2 and 
        create a node with that, head=3.
        In [3:3] our head =3, which is the node req. 
        
        T(n) = T(n/2) + O(1)
            = O(n)
        SC: O(logn), recursive stack
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    /*****************************  SOLUTION 1 ************************************/
    
    // Finds floor(N/2), 1-based indexing
    ListNode* findMiddle(ListNode* head) {
        ListNode *slow = head, *fast = head, *prev = nullptr;
        while(slow && fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return prev;
    }
    
    // TC: O(nlogn)
    TreeNode* logSolution(ListNode* head) {
        // base case: when 0 or 1 node
        if(!head)
            return nullptr;
        if(!head->next)
            return new TreeNode(head->val);
        
        // find the middle node, use it as the end of first list
        ListNode *mid = findMiddle(head);
        // create tree node with next of middle node
        TreeNode* root = new TreeNode(mid->next->val);
        
        // split the two lists
        ListNode *second_head = (mid->next)->next;
        mid->next = nullptr;
        
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(second_head);
        
        return root;
    }
    
    /*************************************** SOLUTION 2 **************************/
    // Finds the total number of nodes in list
    int listCount(ListNode* head) {
        ListNode *curr = head;
        int c = 0;
        
        while(curr) {
            ++c;
            curr = curr->next;
        }
        return c;
    }
    
    // TC: O(n)
    // Create the tree in inorder manner.
    TreeNode* linearSolution(ListNode*& head, int n) {
        // base case: when 0 or 1 node
        if(n == 0)
            return nullptr;
        
        TreeNode *left = linearSolution(head, n/2);
        
        // create the root node
        TreeNode *root = new TreeNode(head->val);
        // go to the next node in list, so that
        // it will middle node in its previous call
        head = head->next;
        root->left = left;
        
        root->right = linearSolution(head, n - n/2 - 1);
        return root;
    }
    
    TreeNode* sortedListToBST(ListNode* head) {
        //return logSolution(head);
        
        // find the number of nodes in list
        int n_nodes = listCount(head);
        return linearSolution(head, n_nodes);
    }
};
