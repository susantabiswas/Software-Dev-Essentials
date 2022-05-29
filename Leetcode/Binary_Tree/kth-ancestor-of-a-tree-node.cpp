/*
    https://leetcode.com/problems/kth-ancestor-of-a-tree-node/
    
    1. Naive way of finding the kth ancestor takes O(k).
      
        while(k > 0 && node != 0) {
                // Find the parent
                node = parent_[node];
                --k;
            }
        return k == 0 ? node : -1; 
    
    But for N queries, it will take O(NK) => TLE
    To make this better, individual queries need to do better than O(K).
    
    We can use binary lifting to achieve this, using this we can get kth ancestor
    in O(logK)
    2. Idea behind binary lifting is to precompute the ancestors of a node, but we don't save all the ancestors for a given node. As finding all K ancestors for a node would result in O(K).
    
    Eg: This ancestor precomputation takes O(KN), which would result in TLE
        for(int i = 1; i <= K; i++) 
            for(int node = 0; node < n; node++)
                // find the ith ancestor
                if(ancestor[node][i-1] != -1)
                    ancestor[node][i] = ancestor[node][i-1];
        
        
    So instead in binary lifting, only log2(N) ancestors are saved for each
    node. This results in O(logN) for each node. 
    
    3. A number can be represented in terms of 2, 3(011) = 2^1 + 2^0, where 0 and 1 are set positions. So in order to be able to return kth ancestor, we compute the ancestors for the positions that can be expressed as 2^i, eg 1, 2, 4, 8, 16.....
    
    So for any k, we evaluate it in terms of ith ancestor from current node.
    Eg: k = 3 (011) => 2^1 + 2^0
    0->1->2->3->4->5->6, node = 5
    
    So this translates to get the 2^0(1st) ancestor of node 5, which is 4. From there get the 2^1(2nd) ancestor of current node (4), i.e 2 and hence we reach the kth node of 5.
    
    4. During precomputation, for a node only its 2^i th ancestors are stored.
    This ensures that we only take O(logN) time to find all 2^i ancestors for each node. Thing to note is odd numbered ancestor(3, 5...) can be found by going to the 
    nearest 2^ith node and from there using 2^0 (1st node) of that nearest node, we can reach the target odd numbered node. Shown in the above example.
    
    Time
    Query: O(log2K)
    Precomputation: O(N * logN)
    
    Space: O(N * logN)
    
*/
class TreeAncestor {
    int height = 0;
    vector<vector<int>> ancestor;
public:
    // TC: O(N * height) = O(N * logN)
    TreeAncestor(int n, vector<int>& parent) {
        // Do the binary lifting precomputation
        height = ceil(log2(n));
        // ancestor[node][i] = 2^i th ancestor of node
        // Eg: ancestor[node][3] = 2^3 (8th) ancestor of node
        // Stores only 2^i th ancestors, 1(2^0), 2(2^1), 4(2^2), 8(2^3), 16(2^4).....
        ancestor.resize(n, vector<int>(height + 1, -1));
        
        // 2^0 = 1st parent info is already present
        for(int i = 0; i < n; i++)
            ancestor[i][0] = parent[i];
        
        // Find the remaining 2^i ancestors
        for(int i = 1; i <= height; i++)
            for(int node = 0; node < n; node++) {
                // This is the max ancestor value known and used to
                // get the value of next ancestor from here
                // Eg To get 2^3(8th) ancestor, we use 2^2(4th) ancestor and 
                // from there get the value of 2^2(4th) ancestor of 4th ancestor
                // node-------->(2^2)4th ancestor ----Get the (2^2)4th ancestor of 4th ancestor--->(2^3)8th ancestor of node
                int farthest_ancestor = ancestor[node][i - 1];
                if(farthest_ancestor != -1)
                    ancestor[node][i] = ancestor[farthest_ancestor][i-1];
            }
    }
    
    // TC: O(log_base2(K))
    int getKthAncestor(int node, int k) {
        // k = 2^a + 2^b + ... 2^g, where a, b,..g are bit positions
        // To get the kth ancestor, we need to perform 2^a + 2^b + ... 2^g many jumps starting 
        // from node
        // Eg: k = 3 => 011: 2^1 + 2^0
        // 0->1->2->3->4->5->6, node = 5
        // This means we 1st have to get to 2^0 (1st) ancestor of node 5 i.e 4, from there we have to get to
        // 2^1(2nd) ancestor of 4 i.e 2. And 2 is also the kth(3rd) ancestor of node 5
        for(int pos = 0; pos <= height; pos++) {
            // If bit is set, jump to pos-th ancestor of current node
            if(k & (1 << pos)) {
                node = ancestor[node][pos]; 
                if(node == -1)
                    return -1;
            }
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */
