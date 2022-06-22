/*
    https://leetcode.com/problems/sentence-similarity-ii/
    
    TC: O(nlogn) + O(m), n = no. of words in similarity dict, m = length of sentence
    
    Since we have to find whether words at ith position in both the sentences are same in same
    way or not, we can map this to a graph problem. Treat each of the words as graph nodes and
    use union find to find similar word clusters.
    Then we iterate through the words in sentence and check whether each of the words at ith position
    are connected by some edge or not.
    Also if some word is not part of similar words array, then that word becomes an individual node and 
    hence won;t have any similar word.
*/
class Solution {
private:
    class UnionFind {
    public:
        vector<int> root, size;
        
        UnionFind(int n) {
            root.resize(n);
            
            for(int i = 0; i < n; i++) 
                root[i] = i;
            size.resize(n, 1);
        }
        
        int getRoot(int a) {
            while(a != root[a]) {
                root[a] = root[root[a]];
                a = root[a];
            }
            return a;
        }
        
        bool Find(int a, int b) {
            return getRoot(a) == getRoot(b);    
        }
        
        bool Union(int a, int b) {
            int root_a = getRoot(a);
            int root_b = getRoot(b);
            
            if(root_a != root_b) {
                if(size[root_a] > size[root_b]) {
                    size[root_a] += size[root_b];
                    root[root_b] = root_a;
                }
                else {
                    size[root_b] += size[root_a];
                    root[root_a] = root_b;
                }
                return true;
            }
            return false;
        }
    };
    
public:
    bool areSentencesSimilarTwo(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        // sentences should be of same length
        if(sentence1.size() != sentence2.size())
            return false;
        
        // In order to use UnionFind, assign index to each word
        // from similar words pair
        int idx = 0;
        // find the no. of unique words
        unordered_map<string, int> words;
        
        for(auto word_pair: similarPairs) {
            if(!words.count(word_pair[0]))
                words[word_pair[0]] = idx++;
            if(!words.count(word_pair[1]))
                words[word_pair[1]] = idx++;
        }
        
        UnionFind uf(words.size());
        // Connect the words to a node cluster
        for(auto similar_words: similarPairs) 
            uf.Union(words[similar_words[0]], words[similar_words[1]]);
        
        for(int i = 0; i < sentence1.size(); i++) 
            // If the words are diff and not similar, or either of the words
            // is not present in the similar dictionary, then we can't perform similarity check
            if(sentence1[i] != sentence2[i] && 
               (!words.count(sentence1[i]) || !words.count(sentence2[i]) || 
                !uf.Find(words[sentence1[i]], words[sentence2[i]])))
                return false;
        
        return true;
    }
};
