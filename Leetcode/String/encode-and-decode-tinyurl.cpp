/*
    https://leetcode.com/problems/encode-and-decode-tinyurl/
    
    TC: 
    Encode: O(1)
    Decode: O(1)
    
    Idea is to 1st decide the number of chars to allow for use in the suffix in the tiny url.
    Here we have taken 62 chars: a-zA-Z0-9, and uses 6 such chars, this gives 62^6 possible suffixes.
    We use to hash table for mapping url -> tiny url and tiny -> url.
    
    Now for a new url, we randomly pick 6 chars and check if that suffix is unique or not, otherwise redo.
    Once we get an unique suffix, we add it to the hash tables.
    
    Decode: use the hash table to return the long url.
*/
class Solution {
private:
    // Hash table which maps url <-> tiny url
    // 1. orig url -> new tiny url
    // 2. new tiny url -> orig url
    unordered_map<string, string> url_to_tiny, tiny_to_url;
    random_device rd;
    // Contains all possible chars for tiny url
    string char_set = "";
    // prefix that will be added for each tiny url
    string url_prefix = "http://tinyurl.com/";
    // size of unique tiny url suffix
    int tiny_url_size = 6;
    
public:
    Solution() {
        // push a-z
        for(char ch = 'a'; ch <= 'z'; ch++)
            char_set.push_back(ch);
        // push A-Z
        for(char ch = 'A'; ch <= 'Z'; ch++)
            char_set.push_back(ch);
        // push 0-9
        for(char ch = '0'; ch <= '9'; ch++)
            char_set.push_back(ch);
    }
    
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        // if the current url as already been encoded, reuse that
        if(url_to_tiny.count(longUrl))
            return url_to_tiny[longUrl];
        
        // init default url suffix
        string url_suffix(tiny_url_size, '#');
        string tiny_url;
        
        while(true) {
            // for each position, add a random char from possible chars
            for(int i = 0; i < tiny_url_size; i++)
                url_suffix[i] = char_set[rd() % char_set.size()];
            // complete url
            tiny_url = url_prefix + url_suffix;
           // check if the url already exists
            if(url_to_tiny.count(tiny_url) == 0)
                break;
        }
        // add the new tiny url to cache
        url_to_tiny[longUrl] = tiny_url;
        tiny_to_url[tiny_url] = longUrl;
        
        return tiny_url;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return tiny_to_url[shortUrl];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
