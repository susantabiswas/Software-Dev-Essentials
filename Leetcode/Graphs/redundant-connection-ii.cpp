/*
    https://leetcode.com/problems/redundant-connection-ii/
    
    TC: O(nlogn)
    SC: O(n)
    
    There can be 3 cases:
    
    case 1: 2 Parents for one node, No cycle
            Either edge [1, 3] or [4, 3] can be removed, but since last needs to be removed, remove [4, 3]
            Solution: remove the 2nd seen edge that contributes to 2 parents
        1
       / \
      v   v
      2   3
     /    ^
    v     |
    4-----|
    
    case 2: 2 Parents for one node, cycle present
            Edges [1, 2] or [4, 2] contribute to 2 parents. Only [4, 2] can be removed since removing [1,2] will make it disconnected.
            Solution: remove the edge that contributes to 2 parents and on the cyclic path
            edge [1, 2] might come after [4, 2] and this will result in candidate1 = [4, 2], candidate2 = [1, 2].
            Once we set the candidates, we disable the candidate2 edge.
            So we need to check post setting the candidates, whether the cycle still exists or not. If we chose 
            [4, 2] as the 2nd candidate, then the cycle would be absent otherwise if candidate2 = [1,2], then cycle 
            will still be present.
         1
       /    \
      v      v
      2<--|   3
     /    | 
    v     |
    4-----|
    
    case 3: Only cycle
            Either edge [1, 2], [2, 4], [4, 1] can be removed, but since last needs to be removed, remove [4, 1]
            Solution: remove the last seen edge that contributes to cycle
         1
       / ^ \
      v  |  v
      2  |  3
     /   | 
    v    |
    4----|
    
    1. We use a parent vector to keep track of parent node for each node
    2. Find the candidate edges that contribute to 2 parents situation. Then disable the last seen candidate edge.
    3. using union find check if cycle is present:
        If cycle is present: track the edge causing cycle
    4. Deal with the individual scenario cases
*/
class Solution {
private:
    class UnionFind {
    public:
        vector<int> root, size;
        UnionFind(int n) {
            root.resize(n);
            size.resize(n, 1);
            for(int i = 0; i < n; i++)
                root[i] = i;
        }
        
        int getRoot(int a) {
            while(a != root[a]) {
                a = root[root[a]];
                a = root[a];
            }
            return a;
        }
        
        bool Union(int a, int b) {
            int root_a = getRoot(a);
            int root_b = getRoot(b);
            
            if(root_a != root_b) {
                if(size[root_a] > size[root_b]) {
                    size[root_a] += size[root_b];
                    root[root_b] = root_a;
                }
                else {
                    size[root_b] += size[root_a];
                    root[root_a] = root_b;
                }
                return true;
            }
            return false;
        }
        
    };
    
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n + 1);
        // Candidate1: First edge seen that is part of 2 parents node
        // Candidate2: Second edge seen that is part of 2 parents node
        vector<int> candidate1, candidate2, disabled_edge;
        // parent[i] = Parent of ith node
        vector<int> parent(n + 1, -1);
        
        // Check if there is an edge that leads to 2 parents
        for(auto edge: edges) {
            int src = edge[0], dst = edge[1];
            // if current destination node already has a parent
            // Track the two candidates
            if(parent[dst] != -1) {
                candidate1 = {parent[dst], dst};
                candidate2 = edge;
                // disable the 2nd seen edge
                disabled_edge = edge;
                break;
            }
            else
                parent[dst] = src;
        }
        
        // Check if there is a cycle
        vector<int> cyclic_edge; 
        for(auto edge: edges) {
            // skip the disabled edge
            if(edge == disabled_edge)
                continue;
            
            int src = edge[0], dst = edge[1];
            // cycle present
            if(uf.Union(src, dst) == false) { 
                cyclic_edge = edge;
                break;
            }
        }
        
        // case1: Only cylic case
        if(candidate1.empty()) 
            return cyclic_edge;
        
        // case2: Cyclic + 2 parents
        // If the candidates were picked correctly, then won't see 
        // a cycle. If we are seeing a cycle, that means we classified candidate 2 wrongly
        if(!cyclic_edge.empty())
            return candidate1;
        
        // case3: Only 2 parents
        return candidate2;
    }
};
