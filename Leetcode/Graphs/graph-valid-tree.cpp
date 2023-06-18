/*
    https://leetcode.com/problems/graph-valid-tree/
    
    Problem is to find presence of cycle in an undirected graph.
    Two things to check:
    1. Whether there are disconnected components. There should be only one component.
    2. There shouldn't be any cycle in the component.
    
    For an undirected graph, Kahn's algorithm and Normal Topological Sort with DFS 
    doesn't work. This is because these assume that the graph is directed, whereas here
    the edges are undirected and hence a->b and a<-b both will exist.
    
    Solution 1: Topological Sort like DFS 
    
    We can modify the topological sort so that we can adapt it to undirected graph. The main
    reason why the normal topological sort doesn't work is because once we go to the child node from
    parent node, we will also see an edge from child to parent node and this can falsely mark a cycle.
    So we pass the parent node each time call to dfs is made, we can check if the edge is to the parent node,
    then ignore the cycle case.
    
    
    Solution 2: Union-Find
    Union Find works with undirected edges and is perfectly suited for this.
*/
class Solution {
private:
    class UnionFind {
    public:
        vector<int> root, size;
        
        UnionFind(int n) {
            root.resize(n), size.resize(n , 1);
            for(int i = 0; i < n; i++)
                root[i] = i;
        }
        
        int getRoot(int idx) {
            while(idx != root[idx]) {
                root[idx] = root[root[idx]];
                idx = root[idx];
            }
            return idx;
        }
        
        bool Union(int a, int b) {
            int rootA = getRoot(a);
            int rootB = getRoot(b);
            
            if(rootA != rootB) {
                if(size[rootA] > size[rootB]) {
                    size[rootA] += size[rootB];
                    root[rootB] = rootA;
                }
                else {
                    size[rootB] += size[rootA];
                    root[rootA] = rootB;
                }
                return true;
            }
            return false;
        }
    };
    
public:
    // Topological sort to detect cycle
    bool topoDfs(int curr, int parent, vector<vector<int>>& g, unordered_set<int>& visited,
                vector<bool>& rec_stack) {
        if(visited.count(curr))
            return false;
        
        // mark as visited
        visited.emplace(curr);
        // add to recursion stack
        rec_stack[curr] = true;
        
        for(auto neighbor: g[curr]) {
            // cycle is present if the current neighbor has an edge to another previously
            // seen node in the current path. It cannot be parent node as the edge is undirected
            // and hence the current node will have an edge to its parent
            if(rec_stack[neighbor] && parent != neighbor)
                return true;
            
            if(!visited.count(neighbor) && topoDfs(neighbor, curr, g, visited, rec_stack))
                return true;
        }
        // remove current from recursion stack
        rec_stack[curr] = false;
        return false;
    }
    
    // SOLUTION 1: Topological Sort using DFS
    // TC: O(V + E)
    // SC: O(V + E)
    bool dfsSol(vector<vector<int>>& g) {
        unordered_set<int> visited;
        
        for(int node = 0; node < g.size(); node++) {
            vector<bool> rec_stack(g.size(), false);
            // graph is disconnected
            if((!visited.empty() && visited.count(node) == 0))
                return false;
            
            // cycle is present
            if(topoDfs(node, -1, g, visited, rec_stack))
                return false;
        }
        return true;    
    }

    // SOLUTION 2: Union-Find
    // TC: O(ElogV)
    // SC: O(V)
    bool unionFindSol(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);
        
        // cycle present
        for(auto edge: edges)
            if(!uf.Union(edge[0], edge[1]))
                return false;
        
        // disconnected components
        int disconnected = 0;
        for(int i = 0; i < n; i++) {
            if(uf.root[i] == i)
                ++disconnected;
            if(disconnected > 1)
                return false;
        }
        
        return true;
    }
    
    bool validTree(int n, vector<vector<int>>& edges) {
        // create the graph
        vector<vector<int>> g(n);
        
        for(auto edge: edges) {
            int src = edge[0], dst = edge[1];
            g[src].push_back(dst);
            g[dst].push_back(src);
        }
        
        // return dfsSol(g);
        return unionFindSol(n, edges);
    }
};

/////////////////////////////////////////////////////////////////////////
/*
    178 · Graph Valid Tree
    https://www.lintcode.com/problem/178/description

    To be a valid tree, these conditions are needed:
    1. There should be no cycle, use Union Find to detect cycle
    2. There should be only one connected component, again use union find for this
*/
class Solution {
private:
    vector<int> root, size;    
public:
    int getRoot(int u) {
        while(root[u] != u) {
            root[u] = root[root[u]];
            u = root[u];
        }
        return u;
    }

    bool Find(int a, int b) {
        int root_a = getRoot(a);
        int root_b = getRoot(b);
        return root_a == root_b;
    }

    void Union(int a, int b) {
        int root_a = getRoot(a);
        int root_b = getRoot(b);

        if(root_a == root_b)
            return;

        if(size[root_a] > size[root_b]) {
            size[root_a] += size[root_b];
            root[root_b] = root_a;
        }
        else {
            size[root_b] += size[root_a];
            root[root_a] = root_b;
        }
    }

    bool cyclePresent(int n, vector<vector<int>>& edges) {
        root.resize(n);
        for(int i = 0; i < n; i++)
            root[i] = i;

        size.resize(n, 1);

        for(auto edge: edges) {
            if(Find(edge[0], edge[1]))
                return true;
            Union(edge[0], edge[1]);
        }
        return false;
    }

    bool isConnected() {
        int conn_components = 0;
        for(int i = 0; i < root.size(); i++)
            if(root[i] == i)
                ++conn_components;
        return conn_components == 1;    
    }

    /**
     * @param n: An integer
     * @param edges: a list of undirected edges
     * @return: true if it's a valid tree, or false
     */
    bool validTree(int n, vector<vector<int>> &edges) {
        return !cyclePresent(n, edges) and isConnected();
    }
};
