/*
    https://leetcode.com/problems/snapshot-array/
    
    We use hash table for storing the changes per column
    col1: HashTable{snapshot_id: val_for_curr_col}
    col2: HashTable{snapshot_id: val_for_curr_col}
    ....
    
    We use another hash table for storing the ongoing changes to 
    each of the columns(index) in the array. We can also use a normal array for this. The only advantage with hash table is if we get a skewed array where only few values are set, then processing time in snap() will increase due to iterating through the 0 set values.
    
    SOLUTION 1: (Faster, takes more space)
    For each snap(), all the columns get a value.
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
        
    SOLUTION 2: (slower, takes lesser space)
    For each snap(), only the columns with got a change since the last snap() get a value.
    Now the idea is whenever we have a snap() call, for each column with a change, we add the current value there with its snapshot_id.
    
    For retrieval i.e get(), we can look at the index(column) key in hash table and then look at the snapshot_id key and return its value.
    TC:
        SnapshotArray(): O(n)
        set(): O(1)
        snap(): O(c * logm), c = no. of columns with a change since last snap(), each insertion in height balanced tree takes logm
        get(): O(logm), m = no. of snapshots
    SC: 
        set(): O(1)
        snap(): O(c), c = no. of columns with a change since last snap(), only those columns get a new value for the current snapshot
        get(): O(1)
        
*/

///////////// SOLUTION 1
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


/////////////// SOLUTION 2

class SnapshotArray {
private:
    int snap_id = 0;
    // <column, {snapshot_id: column val} >
    // Tracks the snapshot_id wise changes for each of the columns
    // Here column is basically the array index
    unordered_map<int, map<int, int> > col_snapshots;
    // Tracks the ongoing changes for each of the column positions
    // <column, value>
    unordered_map<int, int> changes;
public:
    SnapshotArray(int length) {
        for(int i = 0; i < length; i++)
            changes[i] = 0;
    }
    
    void set(int index, int val) {
        changes[index] = val;
    }
    
    int snap() {
        // Add the columns changes since the last snapshot
        for(auto [col, val]: changes)
            col_snapshots[col][snap_id] = val;
        changes.clear();
        return snap_id++;
    }
    
    int get(int index, int snap_id) {
        if(col_snapshots.count(index)) {
            // Check if there is any changed data stored for the given snapshot_id
            // lower_bound will return the 1st >= element
            auto it = col_snapshots[index].lower_bound(snap_id);
            // If there was no data for the snap
            return it != col_snapshots[index].end() && it->first == snap_id ? it->second : (--it)->second;
        }
        return 0;
    }
};
