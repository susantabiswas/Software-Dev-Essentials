/*
    https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/
    
    TC: O(nlogn + nlogn + n) (sorting + union + cluster_traversal)
    SC: O(n)
    
    This problem can be mapped to an undirected graph, where nodes are people.
    Problem asks us to find whether there will be one group in the end or not after
    all the meetings, also if that happens the earliest time when everyone knows each other.
    We can use union find to find the groups where people will know each other and for each cluster we note the last time when a new person joined. We sort the meetings by time so that we add the people to a cluster according to time.
    
*/
class Solution {
private:
    class UnionFind {
    public:
        // earliest_time tracks the last meeting time for a cluster
        vector<int> root, size, earliest_time;
        UnionFind(int n) {
            root.resize(n);
            size.resize(n, 1);
            earliest_time.resize(n, -1);
            
            for(int i = 0; i < n; i++)
                root[i] = i;
        }
        
        int getRoot(int a) {
            while(a != root[a]) {
                root[a] = root[root[a]];
                a = root[a];
            }
            return a;
        }
        
        bool Union(int meeting_time, int a, int b) {
            int root_a = getRoot(a);
            int root_b = getRoot(b);
            
            // earliest _time is only updated for a group when a 
            // new person joins
            if(root_a != root_b) {
                if(size[root_a] > size[root_b]) {
                    size[root_a] += size[root_b];
                    root[root_b] = root_a;
                    earliest_time[root_a] = meeting_time;
                }
                else {
                    size[root_b] += size[root_a];
                    root[root_a] = root_b;
                    earliest_time[root_b] = meeting_time;
                }
                return true;
            }
            return false;
        }
    };
    
public:
    int unionFindSol(vector<vector<int>>& logs, int n) {
        // sort the events by time, so that we update the node
        // connection times according to time. For each root of 
        // disjoint set, earliest_time is updated with the last meeting time
        // that actually connects a new node to the cluster
        sort(logs.begin(), logs.end());
        UnionFind uf(n);
        
        // Group the nodes into clusters
        for(auto log: logs) 
            uf.Union(log[0], log[1], log[2]);
        
        // Check if there is more than 1 node cluster  
        // Inorder for everyone to know each other, there should be only 1 group
        int group_idx = -1;
        for(int i = 0; i < n; i++) {
            if(uf.root[i] == i && group_idx != -1)
                return -1;
            if(uf.root[i] == i) 
                group_idx = i;
        }
                
        return uf.earliest_time[group_idx];
    }
    
    int earliestAcq(vector<vector<int>>& logs, int n) {
        return unionFindSol(logs, n);
    }
};
