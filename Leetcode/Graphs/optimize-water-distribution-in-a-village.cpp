/*
    https://leetcode.com/problems/optimize-water-distribution-in-a-village/

    On looking at the problem description, this seems like a MST problem since it asks for
    minimize cost of placing pipes, but then there is also the option of putting wells for each
    node. That can divert the attention from a typical MST problem.
    
    Prim
    Now if we are thinking in terms of Prim's MST, this scenario would look apt, as in Prim's we consider
    the cut cost for creating the MST. The cost associated with well can be considered a cut cost for that 
    particular node. We can start with all the initial cut cost (cost for well) for each node and then start 
    picking up the traditional cut cost of edge which in this case is the pipe cost.
    
    Kruskal
    If we think of a virtual/dummy house that supplies well connection to each house and has cost associated with 
    it, equal to wells[i]. Then this again becomes a MST problem. House 0 will have a connection to each house, apply normal
    Kruskal's solution.
    
*/
class Solution {
private:
    class UnionFind {
    public:
        vector<int> root, size;
        
        UnionFind(int n) {
            size.resize(n, 1), root.resize(n);
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
    //////////////////////////////////////////////// SOLUTION 1: Prim's MST
    // TC: O(m + ElogE)
    // SC: O(E)
    // m = no. of pipes, n = no. of villages, E = m + n
    int primMST(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        unordered_set<int> visited;
        int total_cost = 0;
        
        // <node, set(<node, cost>)>
        unordered_map<int, vector<array<int, 2> > > graph;
        // create a undirected graph
        for(auto edge: pipes) {
            // In this problem, there can be parallel edges, as well as edges with diff costs
            // Eg: Parallel edge: [1, 2, 5], [1, 2, 1]. Though both pipes go from 1->2, one has a cost of 5, while other has 1
            // Eg: Diff edge cost: [1, 2, 5], [2, 1, 1]. Pipe from 1->2 has cost = 5, pipe from 2->1 has cost = 1.
            // My earlier implementation had unordered_map<int, unordered_map<int, int> > which didn't handle this well as
            // newer edge will overwrite the previous, but when we have a vector containing all the edge values, we will 
            // insert both the edges in the heap and only the smallest cost one will be picked and hence this implementation
            // works like normal without any additional code. Kruskal will also work normally since it works with edges directly 
            // and doesn't need a graph
            int src = edge[0] - 1, dst = edge[1] - 1, cost = edge[2];
            graph[src].push_back({dst, cost});
            graph[dst].push_back({src, cost});
        }
        
        // custom comparator based on the cost for each house
        auto comp = [&](const array<int, 2>& a, const array<int, 2>& b) { return a[1] > b[1]; };
        // <node, cost>
        priority_queue<array<int, 2>, vector<array<int, 2> >, decltype(comp)> min_heap(comp);
        
        // Add the initial cost of setting up the well for each house, treat it an edge to itself
        for(int i = 0; i < wells.size(); i++)
            min_heap.push({i, wells[i]});
        
        int processed = 0;
        // We only need N-1 vertices for MST, so only iterate that many times
        while(processed < n) {
            auto [node, cost] = min_heap.top();
            min_heap.pop();
            
            if(visited.count(node))
                continue;
            // mark as visited
            visited.emplace(node);
            total_cost += cost;
            ++processed;
            
            // Add the connections to unvisited neighbors
            for(auto [dst, pipe_cost]: graph[node]) 
                if(!visited.count(dst)) 
                    min_heap.push({dst, pipe_cost});
        }
        
        return total_cost;
    }
    
    /////////////////////////////////////////// SOLUTION 2: KRUSKAL
    // TC: O(n + ElogE) (adding edges from virtual node + union find)
    // SC: O(E)
    // m = no. of pipes, n = no. of villages, E = m + n
    int kruskalMST(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        // Since each house can have its own well also, we can create a dummy house
        // Assume that all the wells are built here and the pipe to each individual house
        // has a cost given in wells[i]. We can call this as house 0, makes coding easier as
        // others are 1 indexed
        for(int i = 0; i < wells.size(); i++)
            pipes.push_back({0, i+1, wells[i]});
        
        // sort the edges in non-decreasing order
        sort(pipes.begin(), pipes.end(), 
             [](const vector<int>& a, const vector<int>& b)->bool { return a[2] < b[2]; });
    
        UnionFind uf(n+1);
        int processed = 0;
        int total_cost = 0;
        
        for(int i = 0; i < pipes.size() && processed < n; i++) {
            int src = pipes[i][0], dst = pipes[i][1], cost = pipes[i][2];
            if(uf.Union(src, dst))
                total_cost += cost, ++processed;
        }
        
        return total_cost;
    }
    
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        // return primMST(n, wells, pipes);  
        return kruskalMST(n, wells, pipes);
    }
};
