/*
  133. Clone a graph
  https://leetcode.com/problems/clone-graph/submissions/
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
    Node(int val) : val(val) {}
};
*/
class Solution {
public:
    Node* cloneGraph(Node* node) {
        // for storing mapping of node and its clone
        unordered_map<Node*, Node*> h;
        
        queue<Node*> q;
        q.emplace(node);
        
        // create mapping of nodes and their clones
        while(!q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            // create new node
            Node* node = new Node(curr->val);
            h.emplace(curr, node);
            
            for(int i = 0; i < curr->neighbors.size(); i++) {
                if(h.find(curr->neighbors[i]) == h.end())
                    q.emplace(curr->neighbors[i]);
            }
        }
        
        // add the cloned node edges
        q.emplace(node);
        // for tracking visited nodes
        unordered_set<Node*> s;
        // mark visited
        s.emplace(node);
        
        while(!q.empty()) {
            Node* curr = q.front();
           
            q.pop();
            
            for(int i = 0; i < curr->neighbors.size(); i++) {
              
                h[curr]->neighbors.emplace_back(h[curr->neighbors[i]]);
                if(s.find(curr->neighbors[i]) == s.end()) {
                    // mark visited
                    s.emplace(curr->neighbors[i]);
                    q.emplace(curr->neighbors[i]);
                }
            }
        }
        
        return h[node];
    }
};
