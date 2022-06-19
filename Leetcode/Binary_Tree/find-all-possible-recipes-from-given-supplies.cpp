/*
    https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/
    
    SOLUTION 1
    Idea is to convert the recipes and ingredients into a graph, we use an adj list for this.
    The main vertex nodes are the recipes and the neighbors are the items needed.
    
    Then using graph coloring and topological sort, we find whether it is possible to get a recipe 
    made. For a node under processing, mark it as 0 and once processing finishes it becomes 1.
    
    TC: O(V + E)
    SC: O(N)
    
    SOLUTION 2
    Idea is to convert the recipes and ingredients into a graph, we use an adj list for this.
    The main vertex nodes are the ingredients and the neighbors are the recipes needed.
    
    Then using kahn's algo for topological sort, we find whether it is possible to get a recipe 
    made. 
    
    TC: O(V + E)
    SC: O(N)
*/
class Solution {
public:
    bool dfs(string curr, unordered_map<string, vector<string> >& graph,
            unordered_map<string, int>& visited, unordered_set<string>& all_supplies) {
        // mark as processed
        visited[curr] = 0;
        
        // visit unvisited neighbors
        for(auto neighbor: graph[curr]) {
            // if the ingredient is one of the supply ingredients and it's unavailable,
            // then can't create the dish
            if(!graph.count(neighbor) && !all_supplies.count(neighbor))
                return false;
            // if the ingredient is one of the recipes and is already under processing, means there is a cycle
            if(visited.count(neighbor) && visited[neighbor] == 0)
                return false;
            // ingredients is a recipe which has not been processed
            if(!visited.count(neighbor) && !dfs(neighbor, graph, visited, all_supplies))
                return false;
        }
        
        // finish processing
        visited[curr] = 1;
        return true;
    }
    
    // SOLUTION 1: TOPOLOGICAL SORT + GRAPH COLORING
    vector<string> topologicalDFS(unordered_set<string>& all_supplies,
                                 vector<string>& recipes) {
        unordered_map<string, int> visited;
        vector<string> result;
        
        // <recipe, [ingredients,..]>
        unordered_map<string, vector<string> > graph;
        // create a graph with ingredients and recipes. 
        for(int i = 0; i < recipes.size(); i++) {
            for(auto ingredient: ingredients[i])
                graph[recipes[i]].emplace_back(ingredient);
        }
        
        // For each recipe check whether it can be made or not
        for(int i = 0; i < recipes.size(); i++) {
            // Node has not been processed
            if(!visited.count(recipes[i]))
                dfs(recipes[i], graph, visited, all_supplies);
            // If the node has been processed fully
            if(visited[recipes[i]] == 1)
                result.emplace_back(recipes[i]);
        }
        
        return result;
    }
    
    // SOLUTION 2: KAHN'S TOPOLOGICAL SORT
    // TC: O(V + E)
    // SC: O(N)
    vector<string> topologicalKahn(unordered_set<string>& all_supplies,
                                 vector<string>& recipes, vector<vector<string>>& ingredients) {
        unordered_map<string, int> indegree;
        // <ingredients, [recipe,..]>
        unordered_map<string, vector<string> > graph;
        vector<string> result;
        
        // For each recipe, find the dependency ingredients
        // If an ingredient is not in supply, then that counts towrds
        // the indegree
        for(int i = 0; i < recipes.size(); i++) {
            indegree[recipes[i]] = 0;
            for(auto ingredient: ingredients[i]) {
                // ingredient is not supply, hence might be a recipe
                // so it is a dependency
                if(!all_supplies.count(ingredient))
                    ++indegree[recipes[i]];
                graph[ingredient].emplace_back(recipes[i]);
            }
        }
        
        queue<string> q;
        // indegree nodes will always be some recipe, find the
        // ones which has all the req ingredients first
        for(auto [node, degree]: indegree) 
            if(indegree[node] == 0)
                q.emplace(node);
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            
            result.emplace_back(curr);
            // For the current recipe, check if it is an ingredient
            // for some other recipe
            for(auto neighbor: graph[curr]) {
                --indegree[neighbor];
                if(indegree[neighbor] == 0)
                    q.emplace(neighbor);
            }
        }
        
        return result;
    }
    
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_set<string> all_supplies(supplies.begin(), supplies.end());
        // For each node, there are two states: {1 (fully processed), 0 (partially processed)}
        
        // Solution 1
        // return topologicalDFS(all_supplies, recipes);
        // Solution 2: Kahn's Algo
        return topologicalKahn(all_supplies, recipes, ingredients);
    }
};
