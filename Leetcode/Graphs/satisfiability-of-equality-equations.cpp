/*

    https://leetcode.com/problems/satisfiability-of-equality-equations/
    
    TC: O(n) + O(wlog(26)) + O(mlog26) ~ O(n), 
    n = Total no. of equations, w = no. of a == b eq, m = no. of a != b eq

    The questions is more about finding the contradictory equations, like
    a == b and b != a. These two contradict each other, there can be multiple equations
    chained together like a == b, b == c, c == d and a != d.
    Each var and its relation can be mapped to a undirected graph. 
    Looking carefully this is more of validating whether a != d which is whether a and d are connected 
    or not. Eq connects the variables and any != statement basically means that there shouldnt be ny connection
    between the lhs and rhs variables.

    We can use Union Find to efficiently find whether two nodes are connected or not

*/
class Solution {
private:
    class UnionFind
    {
        vector<int> root, size;
        public:
            UnionFind(int n) {
                root.resize(n);
                for(int i = 0; i < n; i++)
                    root[i] = i;

                size.resize(n, 1);
            }

            int getRoot(int u) {
                while(u != root[u]) {
                    root[u] = root[root[u]];
                    u = root[u];
                }
                return u;
            }

            bool Find(int a, int b) {
                return getRoot(a) == getRoot(b);
            } 

            void Union(int a, int b) {
                int root_a = getRoot(a);
                int root_b = getRoot(b);

                if(root_a != root_b) {
                    if(size[root_a] > size[root_b]) {
                        root[root_b] = root_a;
                        size[root_a] += size[root_b];
                    }
                    else {
                        root[root_a] = root_b;
                        size[root_b] += size[root_a];
                    }
                }
            }
    };
public:
    bool equationsPossible(vector<string>& equations) {
        UnionFind uf(26);

        // construct the graph with only the a == b relations
        for(auto equation: equations) 
            // a == b relation
            if(equation[1] == '=') {
                uf.Union(equation[0] - 'a', equation[3] - 'a');
            }
        
        // process the a != b relations: Check whether b is reachable from a or not
        for(auto equation: equations) {
            if(equation[1] == '!' && uf.Find(equation[0] - 'a', equation[3] - 'a'))
                return false;
        }
        return true;
    }
};
