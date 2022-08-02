/*
    https://leetcode.com/problems/similar-string-groups/
    
    TC: O(n^2logn), n = no. of words
    It takes n^2 to explore all the edges and logn for each root find operation
    SC: O(nL), L = length of longest word
    
    Idea is to create a graph and finally check how many connected components are there.
    Each similar word forms an edge. We can use UnionFind to efficiently check whether
    two words are connected in the graph.
    
    Iterate the possible word pairs, and using Union Find connect them. Finally check the no. of 
    components.
*/
class Solution {
private:
    class UnionFind {
    public:
        int n = 0;
        // <node, root_node>
        unordered_map<string, string> root;
        // <node, size of cluster with node as the root>
        unordered_map<string, int> size;
        
        UnionFind(vector<string> words) {
            for(auto word: words)
                root[word] = word, size[word] = 1;
        }
        
        string getRoot(string a) {
            while(root[a] != a) {
                root[a] = root[root[a]];
                a = root[a];
            }
            return root[a];
        }
        
        bool Union(string a, string b) {
            string root_a = getRoot(a);
            string root_b = getRoot(b);
            
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
    // Checks whether two strings are similar according to the definition
    bool isSimilar(string& a, string& b) {
        int diff = 0;
        for(int i = 0; i < a.size() && diff <= 2; i++)
            if(a[i] != b[i])
                ++diff;
        return diff <= 2;
    }
    
    int numSimilarGroups(vector<string>& strs) {
        UnionFind uf(strs);
        
        // For each word pair, check if they are similar. 
        // If they are similar, then join them via edge
        for(int i = 0; i < strs.size(); i++)
            for(int j = i + 1; j < strs.size(); j++) {
                // check if they are similar
                if(isSimilar(strs[i], strs[j]))
                    uf.Union(strs[i], strs[j]);
            }
        
        // No. of connected components in the graph
        int components = 0;
        for(auto [node, root]: uf.root)
            if(node == root)
                ++components;
        return components;
    }
};
