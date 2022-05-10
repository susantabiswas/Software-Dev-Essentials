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
