/*
    https://leetcode.com/problems/design-in-memory-file-system/
    
    getNode(path)
    TC: O(mlogL), 
        L = Length of longest path in terms of path symbols. eg /a/b/c, n = 3
        m = unique paths
    SC: O(mL)
    
    Few approaches:
    1. Map the file system in terms of a graph. Each path symbol is mapped as a graph node.
    2. Use Trie for managing the file system. Each Trie Node is a symbol of file system path. Whenever we need to go to a path, then traverse the Trie till that node. Get a ptr to that node and then perform teh opeartions like ls, getContent, addContent etc.
    3. Use the above approach + Hash table to map <file_path: TrieNode address>. This way we don't need to traverse the Trie everytime we want to get to a path which already exists.
    
*/
class FileSystem {
private:
    struct TrieNode {
        // <folder name, TrieNode addr>
        unordered_map<string, TrieNode*> leaves;
        // Whether the symbol is file or not
        bool is_file = false;
        // Contents if the symbol is file
        string content;
        // Path from root / till current symbol and name of symbol
        // Eg path: /a/b/c, name: c
        string path, name;
        
        TrieNode(string path, bool is_file, string name): 
            path(path), is_file(is_file), name(name) {}
    };
    
    // Root node of file system
    TrieNode* root = new TrieNode("/", false, "/");
public:
    FileSystem() {
    }
    
    // Gets a file system node present at the end
    // of given path. In case of missing nodes in the
    // path, they are created
    TrieNode* getNode(string path) {
        istringstream ss(path);
        string folder;
        
        TrieNode* curr = root;
        // ignore the empty token
        getline(ss, folder, '/');
        
        string curr_path = "/";
        
        // Just like trie for strings, we create the 
        // filesystem nodes and traverse the path forward
        while(getline(ss, folder, '/')) {
            curr_path += folder;
            // By default we create the node as a folder
            if(curr->leaves.count(folder) == 0)
                curr->leaves[folder] = new TrieNode(curr_path, false, folder);
            curr = curr->leaves[folder];
        }
        return curr;
    }
    
    vector<string> ls(string path) {
        vector<string> files;
        // Get the node for the given path
        TrieNode* node = getNode(path);
        
        // If path leads to a file
        if(node->is_file)
            return { node->name };
        
        // For folder, add all the files under it
        for(auto [leaf_name, leaf_node]: node->leaves)
            files.push_back(leaf_name);
        
        sort(files.begin(), files.end());
        return files;
    }
    
    void mkdir(string path) {
        TrieNode* node = getNode(path);
    }
    
    void addContentToFile(string filePath, string content) {
        // Get the node leading to that file and append its content
        TrieNode* node = getNode(filePath);
        node->is_file = true;
        node->content += content;
    }
    
    string readContentFromFile(string filePath) {
        TrieNode* node = getNode(filePath);
        return node->content;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */
