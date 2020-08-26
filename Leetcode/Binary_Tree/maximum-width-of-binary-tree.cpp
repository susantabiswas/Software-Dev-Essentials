/*
    https://leetcode.com/problems/maximum-width-of-binary-tree/
    
    Approach 1:
    My first approach was to use normal BFS with null + non null nodes as well.
    Idea was to push 2 child nodes(left + right) for a null node and for non-null node
    push its childrean, incase there was only one, then the other child is pushed as null.
    This solution resulted in timeout.
    
    Approach 2:
    A binary tree can also be saved in an array, the way we see in a heap implementation. To save a binary
    tree in an array like DS, for ith index node, we save its left child at 2*i, right: 2*i + 1, when 1 based indexing is
    considered.
    So now in that array if we knew the the range of elements belonging to diff levels, we could have just taken the diff
    of last and first node index and keep track of this for all the levels. So to know the level, we can use BFS.
        1
       / \
      2   NULL
    eg: 1(1) 2(2) NULL(3), (1 based index)
    
    We do BFS, and we associate each node with the index where it would have been saved incase it was stored in an array.
    Now since in BFS, we can track the first and last node, we check the diff of index position between them and compare 
    with max width found so far.
    
    Challenge(Applicable to lang. with no native big Integer support): Since the index numbers can get too big, the case needs to be handled well.
        If we use a signed int, then for bigger numbers that result is a -ve num, now
        to find the diff in indices, (-A) - (+B), where A and B both are big and A > max limit so it is -ve, and has
        an undefined behavior in C++.
        So to solve this, we can use an unsigned int/long, so even with big nums, there is 
        a defined behavior using % N incase of unsigned.
*/


class Solution {
public:
    // Tree node with index position
    struct NodeIndex {
        TreeNode *node = nullptr;
        unsigned long index = -1;
        NodeIndex(TreeNode *node, unsigned long idx): node(node), index(idx) {};
    };
    
    // TC: O(N)
    int widthOfBinaryTree(TreeNode* root) {
        queue<NodeIndex> q;
        unsigned long max_width = 0;
        // keeps track of first and last position index
        unsigned long first = -1, last = -1;
        
        q.emplace(NodeIndex(root, 1));
        int n_level = q.size();
        
        // Do a normal BFS, and for each level find the
        // diff of first and last element index if they are stored in array like storage 
        while(!q.empty()) {
            NodeIndex curr = q.front();
            q.pop();
            --n_level;
            
            if(first == -1)
                first = curr.index;
            
            if(curr.node->left)
                q.emplace(NodeIndex(curr.node->left, 2 * curr.index));

            if(curr.node->right)
                q.emplace(NodeIndex(curr.node->right, 2 * curr.index + 1));
            
            // end of level
            if(n_level == 0) {
                last = curr.index;
                // update max width if applicable
                max_width = max(max_width, last - first + 1);
                n_level = q.size();
                // reset
                first = -1, last = -1;
            }
        }
        
        return max_width;
    }
};
