/*
    https://leetcode.com/problems/snapshot-array/
    
    We use hash table for storing the changes per column
    col1: HashTable{snapshot_id: val_for_curr_col}
    col2: HashTable{snapshot_id: val_for_curr_col}
    ....
    
    We use another hash table for storing the ongoing changes to 
    each of the columns(index) in the array. We can also use a normal array for this. The only advantage with hash table is if we get a skewed array where only few values are set, then processing time in snap() will increase due to iterating through the 0 set values.
    
    Now the idea is whenever we have a snap() call, for each column, we add the current value there with its snapshot_id.
    
    For retrieval i.e get(), we can look at the index(column) key in hash table and then look at the snapshot_id key and return its value.
    TC:
        set(): O(1)
        snap(): O(n)
        get(): O(1)
    SC: 
        set(): O(1)
        snap(): O(n), each column gets a new value for the current snapshot
        get(): O(1)
        
*/
class SnapshotArray {
private:
    int snap_id = 0;
    // <column, {snapshot_id: column val} >
    // Tracks the snapshot_id wise changes for each of the columns
    // Here column is basically the array index
    unordered_map<int, unordered_map<int, int> > col_snapshots;
    // Tracks the ongoing changes for each of the column positions
    // <column, value>
    unordered_map<int, int> changes;
public:
    SnapshotArray(int length) {
    }
    
    void set(int index, int val) {
        changes[index] = val;
    }
    
    int snap() {
        // Add the columns changes since the last snapshot
        for(auto [col, val]: changes)
            col_snapshots[col][snap_id] = val;
        return snap_id++;
    }
    
    int get(int index, int snap_id) {
        return col_snapshots.count(index) ? 
            col_snapshots[index][snap_id] : 0;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
