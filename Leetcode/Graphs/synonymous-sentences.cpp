/*
    https://leetcode.com/problems/synonymous-sentences/
    
    Solution 1: Union Find
    Idea is to find the word clusters that are synonyms of each other. We do this 
    using union find. Once we know the word clusters, use backtracking for putting
    synonyms at each word position in the original sentence.
    
    Solution 2: BFS
    We create a normal graph. To mimic the above union-find method's behavior of finding
    synonym clusters, we make use of normal graph traversal. In each subsequent level of BFS, a
    new synonym will be added via edge neighborhood. In BFS, we pass the initial sentence in tokenized
    form and replace one word at a time and add to queue.
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
    void formSentence(int idx, vector<string>& text, unordered_map<string, int>& words,
                      unordered_map<int, vector<string>>& word_clusters, 
                      unordered_set<string>& result, unordered_map<string, int> word_to_cluster) {
        
        // base case
        if(idx == text.size()) {
            // convert tokens to a joined sentence
            string sentence;
            for(auto word: text) {
                if(!sentence.empty())
                    sentence += ' ';
                sentence.append(word);
            }
            result.emplace(sentence);
            return;
        }
        string orig_word = text[idx];
        
        formSentence(idx+1, text, words, word_clusters, result, word_to_cluster);
        // If current word has no synonyms
        if(!words.count(orig_word))
            return;
        // for the word at current position, replace it with all the synonyms
        for(auto word: word_clusters[word_to_cluster[orig_word]]) {
            text[idx] = word;
            formSentence(idx + 1, text, words, word_clusters, result, word_to_cluster); 
        }
    }
    
    // SOLUTION 1: Union Find
    // TC: O(nlogn) + O(nlogn) + O(w^L) + O(mlogm)
    // union operation + reverse cluster mapping + backtracking + sorting
    // n: no. of words in synonyms, w = max no. of words in a cluster, L = No. of words in sentence text
    // m = no. of sentences
    vector<string> unionFindSol(vector<vector<string>>& synonyms, string text) {
        // In order to use UnionFind, assign index to each word
        // from similar words pair
        int idx = 0;
        // find the no. of unique words
        unordered_map<string, int> words;
        
        for(auto word_pair: synonyms) {
            if(!words.count(word_pair[0]))
                words[word_pair[0]] = idx++;
            if(!words.count(word_pair[1]))
                words[word_pair[1]] = idx++;
        }
        
        UnionFind uf(words.size());
        // Connect the words to a node cluster
        for(auto similar_words: synonyms) 
            uf.Union(words[similar_words[0]], words[similar_words[1]]);
        
        // Create a mapping: <cluster idx: [words]>
        unordered_map<int, vector<string> > word_clusters;
        unordered_set<string> unique_sentences;
        // <word, index of cluster>
        unordered_map<string, int> word_to_cluster;
        
        for(auto [word, idx]: words) {
            int root_idx = uf.getRoot(idx);
            word_clusters[root_idx].emplace_back(word);
            word_to_cluster[word] = root_idx;
        }
        
        // split the words into word tokens
        vector<string> text_words;
        istringstream ss(text);
        string word;
        while(getline(ss, word, ' ')) 
            text_words.push_back(word);
        
        formSentence(0, text_words, words, word_clusters, unique_sentences, word_to_cluster);
        
        vector<string> result(unique_sentences.begin(), unique_sentences.end());
        sort(result.begin(), result.end());
        
        return result;
    }
    
    // TC: O(m^nlog(m^n)), n = no. of words in sentence, m = no. of synonyms
    // worst case when all n words are same and m synonyms exists for those words
    // sentence: "joy joy joy joy", synonyms = ["joy", "happy", "cheerful"]
    // For each word , there are 3 options => 3 * 3 * 3 * 3 => 3 ^ 4
    vector<string> bfsSol(vector<vector<string>>& synonyms, string text) {
        // create a graph
        unordered_map<string, vector<string>> graph;
        for(auto similar_words: synonyms) {
            graph[similar_words[0]].emplace_back(similar_words[1]);
            graph[similar_words[1]].emplace_back(similar_words[0]);
        }
        
        set<vector<string>> sentences;
        queue<vector<string>> q;
        
        // break the initial sentence into word tokens
        // Working with list of words is easier 
        istringstream ss(text);
        string word;
        vector<string> sentence;
        while(getline(ss, word, ' ')) 
            sentence.emplace_back(word);
        q.emplace(sentence);
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            
            sentences.emplace(curr);
            
            for(int i = 0; i < curr.size(); i++) {
                string orig_word = curr[i];
                // replace the current word with its neighbors (synonyms)
                for(auto word: graph[orig_word]) {
                    curr[i] = word;
                    if(!sentences.count(curr))
                        q.emplace(curr);
                }
                // revert the change
                curr[i] = orig_word;
            }   
        }
        
        vector<string> result;
            
        // join the sentence tokens 
        for(auto curr: sentences) {
            string sentence;
            for(int i = 0; i < curr.size(); i++) { 
                if(!sentence.empty())
                    sentence.append(" ");
                sentence.append(curr[i]);
            }
            result.emplace_back(sentence);
        }
        
        return result;
            
    }
    
    vector<string> generateSentences(vector<vector<string>>& synonyms, string text) {
        return unionFindSol(synonyms, text);
        // return bfsSol(synonyms, text);
    }
};
