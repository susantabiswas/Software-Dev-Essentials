/*
    https://leetcode.com/problems/clone-graph/
    
    Sol1: DFS
    1. For the curr node, create a clone and add to node mapping
    2. Explore its adj neighbors:
        1. If neighbor is unvisited: Recurse further with that node as root
        2. Create the neighbor link in the cloned root 
        
    Sol2: BFS
    1. Add the curr in the queue, create the node map 
    2. Explore its adj neighbors:
        1. If neighbor is unvisited: Add neighbor node as root in queue, create the node map
        2. Create the neighbor link in the cloned root using the node map 
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    // Sol 1: DFS
    // TC: O(N)
    // SC: O(N)
    Node* cloneGraphDfs(Node* curr, unordered_map<Node*, Node*>& node_map) {
        Node* clone_root = new Node(curr->val);
        // mark as visited
        node_map.emplace(curr, clone_root);
        // make a clone of current node's neighbors
        for(auto neighbor: curr->neighbors) {
            // recurse further only if the node is unvisited, otherwise it will create a cycle
            if(!node_map.count(neighbor)) {
                Node* clone_node = new Node(neighbor->val);
                cloneGraphDfs(neighbor, node_map);
            }
            // add the clone of neighbor to the curr clone root node
            clone_root->neighbors.emplace_back(node_map[neighbor]);
        } 
        return node_map[curr];
    }
    
    // Sol2: BFS
    // TC: O(N)
    // SC: O(N)
    Node* cloneGraphBfs(Node* curr, unordered_map<Node*, Node*>& node_map) {
        Node* clone = new Node(curr->val);
        // mapping of root nodes
        node_map.emplace(curr, clone);
        queue<Node*> q;
        q.emplace(curr);
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            
            for(auto neighbor: curr->neighbors) {
                // if current neighbor is unvisited, add for traversal
                if(!node_map.count(neighbor)) {
                    Node* cloned_node = new Node(neighbor->val);
                    q.emplace(neighbor);
                    node_map[neighbor] = cloned_node;
                }
                // add the cloned node as neighbour to curr cloned node
                node_map[curr]->neighbors.emplace_back(node_map[neighbor]);
            }
        }
        return node_map[curr];
    }
    
    Node* cloneGraph(Node* node) {
        if(!node)
            return nullptr;
        // <old node, cloned node>
        unordered_map<Node*, Node*> node_map;
        // start with the clone of root node
        return cloneGraphDfs(node, node_map);
        // return cloneGraphBfs(node, node_map);
    }
};
