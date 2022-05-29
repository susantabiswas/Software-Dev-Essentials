/*
    https://leetcode.com/problems/min-cost-to-connect-all-points/
    
    This problem can be converted to a min spanning tree prob. 
    We need to create a strongly connected graph and apply MST alogs 
    to find the MST cost.
*/
class Solution {
private:
    struct WeightedEdge {
        int dist = 0;
        int src, dst;
        WeightedEdge(int dist, int src, int dst): dist(dist), src(src), dst(dst) {}; 
    };
    
    // For Prim's 
    struct WeightedVertex {
        int label;
        int cost = 0;
        WeightedVertex(int label, int cost): label(label), cost(cost) {};
    };
    
    // Union Find with path compression and rank
    // TC: O(logn)
    class UnionFind {
        private:
            vector<int> root_, size_;
        public:
            UnionFind(int n) {
                root_.resize(n);
                size_.resize(n, 1);
                // init each node is it's own root
                for(int i = 0; i < n; i++)
                    root_[i] = i;
            }
        
            int getRoot(int v) {
                while(root_[v] != v) {
                    root_[v] = root_[root_[v]];
                    v = root_[v];
                }
                return root_[v];
            }
        
            void Union(int a, int b) {
                int root_a = getRoot(a);
                int root_b = getRoot(b);
                // make the smaller subtree part of bigger
                if(size_[root_a] > size_[root_b]) {
                    root_[root_b] = root_a;
                    size_[root_a] += size_[root_b];
                }
                else {
                    root_[root_a] = root_b;
                    size_[root_b] += size_[root_a];
                }
            }
            // check if vertex a and b are connected
            bool Find(int a, int b) {
                int root_a = getRoot(a);
                int root_b = getRoot(b);
                return root_a == root_b;
            }
    };
    
public:
    // MST using Kruskal's algo
    // TC: O(VE + ElogV)
    int kruskalMST(int n, vector<WeightedEdge>& edges) {
        int cost = 0;
        // sort the edges by weight
        sort(edges.begin(), edges.end(), [](WeightedEdge& a, WeightedEdge& b) -> bool {
            return a.dist < b.dist;
        });
        
        UnionFind ob(n);
        
        for(auto edge: edges) {
            int src = edge.src, dst = edge.dst;
            if(!ob.Find(src, dst)) {
                ob.Union(src, dst);
                cost += edge.dist;
            }
        }
        return cost;
    }
    
    // MST using Prim's algo
    // TC: O(VE + ElogE)
    int primMST(vector<vector<int>>& points) {
        int cost = 0;
        int n = points.size();
        // No. of vertices added to MST, we can avoid unnecessary computation once all 
        // the vertices are visited once
        int processed_vertices = 0;
        // visited[i] = whether node i has been visited before
        vector<bool> visited(n, false);
        
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                    function<bool(pair<int, int>, pair<int, int>)>>
                min_heap([](const pair<int, int>& a, const pair<int, int>& b) -> bool {
                    return a.second > b.second;
                });
        // start with init vertex 0, it will have 0 cut cost
        min_heap.emplace(make_pair(0, 0));
        
        while(processed_vertices < n) {
            auto curr = min_heap.top();
            min_heap.pop();
            
            // only process if it's not visited
            if(!visited[curr.first]) {
                ++processed_vertices;
                visited[curr.first] = true;
                cost += curr.second;
                
                // add neighbours
                for(int dst = 0; dst < points.size(); dst++) {
                    if(!visited[dst])
                        min_heap.emplace(make_pair(dst,
                                                  abs(points[curr.first][0] - points[dst][0]) 
                                                    + abs(points[curr.first][1] - points[dst][1])));
                }
            }
        }
        
        return cost;
    }
    
    int minCostConnectPoints(vector<vector<int>>& points) {
        /******* Kruskal's MST ******/
        // create graph, make edges from each vertex to all other
//         vector<WeightedEdge> edges;
        
//         for(int src = 0; src < points.size(); src++)
//             for(int dst = 0; dst < points.size(); dst++) {
//                 if(src != dst) {
//                     edges.emplace_back(WeightedEdge(abs(points[dst][0] - points[src][0]) 
//                                                     + abs(points[dst][1] - points[src][1]),
//                                                     src, dst));
//                 }        
//             }
        
//         int mst_cost = kruskalMST(points.size(), edges);
        
        
        /******* Prim's MST ******/
        int mst_cost = primMST(points);
        
        
        return mst_cost;
    }
};
