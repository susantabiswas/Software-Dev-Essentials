/*
    https://leetcode.com/problems/design-search-autocomplete-system/
    
    This is a generalized solution which works for top k suggestions and suitable for read loads.
    Reads are light weight, we perform the computation only when we have finished processing a query and not
    during a read query.
    
    For normal queries it is O(1) of effort in terms of processing.
    
    We store the sentences and their frequency in vectors.
    Initially these are initialized with values in AutocompleteSystem().
    Each Trie Node has a vector that keeps track of suggestions in sorted manner. 
    Every time we want to add a string to trie, we iterate through the trie nodes and for each node, we add the index of 
    current string to the suggestions array. Then sort the array based on the metric and pop out the last element if the size exceeds k.
    
    Saving only the index of a string has an advantage. Since we only save the index, we can easily make updates
    to the frequency for a string without worrying about individual updates in the trie nodes. Though we do need to sort again to reflect the
    new order of suggestions.
    
    There is a curr ptr which is used to iterate through the trie during the query. It starts with root of trie and for each char in input(c), 
    we take a step forward. In case the current char is not found, that means the current prefix doesn't exist in the trie and any char till
    # won't have any suggestions, so we set the curr iterator to nullptr to indicate that there is no point searching.
    
    When the query ends with #, we reset curr iterator, check if the prefix is new or not. Based on that we add it to the list of sentences.
    Then we add the strint to Trie, updating all the nodes going down the trie.

    TC:
        n = no. of sentences, L = length of longest sentence, k = No. of suggestions to show for each char
        m = Length of query string
        
        AutocompleteSystem: O(n * L * (k + klogk) ) ~ O(nL), Inserting each sentence * (searching + sorting the suggestions for each node)
        
        insert: O(L * (k + klogk)) ~ O(L), k = 3, Iterate through L nodes and for each node update the suggestions by sorting
        
        search: O(1), This is when skipping the copy of array elements
        
        input: O(nL (Searching) + m * (k + klogk) (Trie update)), O(1) for others. Since all the nodes already have suggestions, it doesnt take extra processing.
                            When we have '#' and the query string is new, we need to add it to the array and then update trie 
    
        Space:
        O(n * L)
*/
class AutocompleteSystem {
private:
    struct TrieNode {
        unordered_map<char, TrieNode*> leaves;
        // Stores the index of hot sentence
        vector<int> suggestions;
    };
    // Tracks the root of trie
    TrieNode* root_ = nullptr;
    // Trie iterator for a given query
    TrieNode* curr = nullptr;
    string prefix;
    const int TOP_K = 3;
    
    // Hot sentences 
    vector<string> sentences;
    // freq[i] = Frequency of ith hot sentence
    vector<int> freq;
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        // Root of trie
        root_ = new TrieNode();
        // Set the query iterator to the trie root
        curr = root_;
        // Save the initial list of sentences and their frequencies
        this->sentences = sentences;
        this->freq = times;
        
        for(int idx = 0; idx < sentences.size(); idx++) 
            insert(sentences[idx], idx);
    }
    
    void insert(string str, int idx) {
        // Trie Iterator 
        TrieNode* root = root_;
        
        // Add the word char by char
        for(char ch: str) {
            if(root->leaves.count(ch) == 0)
                root->leaves[ch] = new TrieNode();
            root = root->leaves[ch];
            
            // Check if the new string already exists in the hot sentences or not, if not add
            if(find(root->suggestions.begin(), root->suggestions.end(), idx) == root->suggestions.end())
                root->suggestions.emplace_back(idx);
            
            // Now sort the hot sentences based on the comparison metric
            sort(root->suggestions.begin(), root->suggestions.end(), [this](int idx1, int idx2) -> bool {
                if(freq[idx1] == freq[idx2]) 
                    return sentences[idx1] < sentences[idx2];
                return freq[idx1] > freq[idx2];
            });
            
            // Now if we have more than k suggestions, remove the extra
            if(root->suggestions.size() > TOP_K)
                root->suggestions.pop_back();
                
            
        }
    }    
    
    vector<string> search(char ch) {
        vector<string> suggestions;
        // Check if the trie iterator is not null and 
        // current char exists as well
        if(curr && curr->leaves.count(ch)) {
            curr = curr->leaves[ch];
            for(auto idx: curr->suggestions)
                suggestions.emplace_back(sentences[idx]);
        }
        // Current char doesn't exist, so there won't be any match for this
        // query onwards. So set the iterator to null
        else
            curr = nullptr;
        return suggestions;
    }
    
    vector<string> input(char c) {
        // End of query
        if(c == '#') {
            // Add the prefix to Trie
            // Check if the prefix is already added or not
            auto it = find(sentences.begin(), sentences.end(), prefix);
            // New sentence found, update its frequency
            if(it == sentences.end()) {
                sentences.emplace_back(prefix);
                freq.emplace_back(1);
                insert(prefix, sentences.size()-1);
            }
            // The prefix already exists
            else {
                int idx = it - sentences.begin();
                freq[idx] += 1;
                insert(prefix, idx);
            }
                
            // Now that query has ended, reset current iterator and query prefix
            curr = root_;
            prefix.clear();
            
            return vector<string>{};
        }
        // Add the current char to the ongoing query prefix
        prefix += c;
        // Get the suggestions for the prefix ending at current char
        return search(c);
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */
