/*
    https://leetcode.com/problems/lexicographically-smallest-equivalent-string/
    
    TC: O(nlog(128) + m), n = length of s1, m = length of baseStr
    SC: O(128)
    
    Idea is to make cluster of node chars and track the smallest node in each cluster.
    Then for each of the chars in baseStr, replace with the smallest in clsuter.
*/
class Solution {
private:
    class UnionFind {
    public:
        int n = 128;
        vector<int> root, size;
        // tracks the smallest char in the cluster
        vector<char> smallest;
        
        UnionFind() {
            root.resize(n);
            size.resize(n, 1);
            smallest.resize(n);
            
            for(int i = 0; i < n; i++)
                root[i] = i;
            for(int i = 0; i < n; i++)
                smallest[i] = (char)i;
        }
        
        int getRoot(int a) {
            while(a != root[a]) {
                root[a] = root[root[a]];
                a = root[a];
            }
            return a;
        }
        
        bool Find(int a, int b) {
            return getRoot(a) == getRoot(b);
        }
        
        // While doing the Union, we update the smallest node in the cluster as well
        bool Union(int a, int b) {
            int root_a = getRoot(a);
            int root_b = getRoot(b);
            
            if(root_a != root_b) {
                if(size[root_a] > size[root_b]) {
                    size[root_a] += size[root_b];
                    root[root_b] = root_a;
                    // update the smallest node in cluster if needed
                    if(smallest[root_b] < smallest[root_a])
                        smallest[root_a] = smallest[root_b];
                }
                else {
                    size[root_b] += size[root_a];
                    root[root_a] = root_b;
                    // update the smallest node in cluster if needed
                    if(smallest[root_a] < smallest[root_b])
                        smallest[root_b] = smallest[root_a];
                }
                return true;
            }
            return false;
        }
    };
    
public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        UnionFind uf;
        // Treat the chars are nodes and the equivalence relation as an edge
        // Do Union Opeartion to form node clusters
        for(int i =0; i < s1.size(); i++)
            uf.Union(s1[i], s2[i]);
        
        string result;
        // for each char in baseStr, pick the smallest in the cluster
        for(int i = 0; i < baseStr.size(); i++) 
            result += uf.smallest[uf.getRoot(baseStr[i])];
        return result;
    }
};
