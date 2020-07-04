/*
    https://leetcode.com/problems/search-suggestions-system/submissions/
*/
class Solution {
public:
    // SOLUTION 1
    // Using Binary search
    // TC: Binary Search + Sorting
    //      O(L ^ 2 * logn + m*nlogn), L: length of word to find, m: length of longest word
    // For binary search: 1char: logn
    //                     2chars: 2 * logn
    //                      ... L chars: L * logn
    //                      L ^ 2 * logn
    //
    // We do Binary search on the sorted array of words, then if we a hit for the prefix, then also
    // check its next 2 words if they also contain the prefix or not.
    vector<vector<string>> suggesteBinarySearch(vector<string>& products, string searchWord) {
        vector<vector<string>> result;
        string prefix;
        
        /// Since the order of sugggestion needs to be in lexographical order
        // we sort it before hand 
        sort(begin(products), end(products));
        
        for(const char c: searchWord) {
            // add the current char to prefix
            prefix += c;
            // search for the current prefix amongst the words
            auto it = lower_bound(begin(products), end(products), prefix);
            vector<string> suggestion;
            // check if the current prefix is present, also check the next 2 words if present
            for(int i = 0; i < 3 && it + i < products.end(); i++) {
                if((*(it + i)).find(prefix) != string::npos)
                    suggestion.emplace_back(*(it + i));
                else
                    break;
            }
            result.emplace_back(suggestion);
        }
            
        return result;
    }
    
    // SOLUTION 2
    // Using Trie
    /*
        TC: Sorting + Trie Creation + Trie Query
        TC: O(m*nlogn + m*n + L^2), L: length of word to find, m: length of longest word,
                                        n: No. of words
                                        
        We create a Trie where for each of the nodes we also save the suggestions for that char.
        In order to give 3 lexographically sorted suggestions, we sort the array before hand and then 
        insert the words in that order in Trie so that the suggestions gets filled with releveant words.
        
    */
    struct Trie {
        unordered_map<char, Trie*> leaves;
        // Lexographically sorted suggestion till each char 
        vector<string> suggestions;
    };
    
    void insertTrie(Trie* root, string word) {
        for(const char& c: word) {
            if(root->leaves.find(c) == root->leaves.end())
                root->leaves[c] = new Trie();
            root = root->leaves[c];
            
            // Add the current word as suggestion if we dont have enough suggestions
            if(root->suggestions.size() < 3)
                root->suggestions.emplace_back(word);
        }
    }
    
    
    vector<vector<string>> suggestionTrie(vector<string>& products, string searchWord) {
        vector<vector<string>> result(searchWord.size());
        // sort the words 
        sort(begin(products), end(products));
        // Create the Trie, since the words are sorted
        // so the suggestions are also lexographically sorted
        Trie *root = new Trie();
        for(const string &word: products)
            insertTrie(root, word);
        
        string prefix;
        for(int i = 0; i < searchWord.size(); i++) {
            auto it = root->leaves.find(searchWord[i]);
            if(it != root->leaves.end()) {
                root = it->second;
            }
            else
                break;
            // add suggestions if any for the current char
            result[i] = root->suggestions;
        }
        return result;
    }
    
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        return suggesteBinarySearch(products, searchWord);
        // return suggestionTrie(products, searchWord);
    }
};
