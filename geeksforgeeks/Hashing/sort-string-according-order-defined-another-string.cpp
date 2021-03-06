/*
    https://www.geeksforgeeks.org/sort-string-according-order-defined-another-string/
    
*/
// Global hash table with order for each char,
// used in comparator
unordered_map<char, int> order;

struct Comp {
    const bool operator()(const string &a, const string &b) const {
        int i = 0, j = 0;
        /// If any smaller of b appears at the same pos as a
        while(i < a.size() && j < b.size()) {
            if(order[a[i]] > order[b[j]])
                return false;
            else if(order[a[i]] < order[b[j]])
                return true;
            ++i, ++j;
        }
        // When the entire smaller string is contained in longer
        // A can only appear first if its length is smaller
        return b.size() > a.size();    
    }    
};

void sort_by_order( vector <string> &words, string &alphabets )
{   
    int priority = 1;
    // Init the char order table
    for(const char &c: alphabets)
        order[c] = priority++;
        
    sort(words.begin(), words.end(), Comp());
}
