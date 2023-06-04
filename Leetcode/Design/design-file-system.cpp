/*
    https://leetcode.com/problems/design-file-system/
    
    createPath
        TC: O(n), length of path
    get()
        TC: O(1)
        
    SC: O(n * m), m = no. of paths, n = longest path length
    
    We use a hash table to keep track of paths added so far.
    One special path is added: "". This is not a valid path
    on its own but it serves to check for valid parent paths
    "" is a valid parent path(without parent path's trailing /)
    eg: /a, parent path: "". This should be valid, so we keep the parent path
    "" as valid
    
    createPath:
        Extract the parent path without the trailing /. Then check if that 
        exists as one of the previously added paths. If the parent path exists,
        then the path is valid otherwise not.
*/
class FileSystem {
private:
    unordered_map<string, int> paths = {{"", -1}};
public:
    FileSystem() {
    }
    
    bool createPath(string path, int value) {
        if(path.empty() || path[0] != '/' ||
          paths.count(path))
            return false;
        
        // extract out the parent path
        // eg /a/b/c, parent_path: /a/b
        int i = 0;
        for(i = path.size() - 1; i >= 0 && path[i] != '/'; i--);
        string parent_path = path.substr(0, i);
        
        // for the current path, it is only valid if the
        // parent path exists
        if(paths.count(parent_path) == 0)
            return false;
        
        paths[path] = value;
        return true;
    }
    
    int get(string path) {
        // "" is a special path saved for operation.
        // But it is not a valid path
        if(path.empty())
            return -1;
        return paths.count(path) ? paths[path] : -1;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */
