#include "Common.h"

std::vector<int> get_fail(std::string& str){
    std::vector<int> fail(str.size(), 0);
    int j = 0;
    for(int i = 1; i < str.size(); ++i){
        while(str[i] != str[j] && j > 0) j = fail[j - 1];
        if(str[i] == str[j]) fail[i] = ++j;
    }
    return fail;
}

std::vector<int> get_fail2(std::string& str){
    std::vector<int> fail(str.size(), 0);
    int i=0;
    for(int j=1;j<str.size();++j){
        while(i>0&&str[i]!=str[j]) i=fail[i-1];
        if(str[i]==str[j]) fail[j]=++i;
    }
    return fail;
}

std::vector<int> kmp2(std::string& str, std::string& pattern){
    std::vector<int> fail(std::move(get_fail2(pattern)));
    std::vector<int> result;
    int j=0;
    for(int i=0;i<str.size();++i){
        while(j>0&&str[i]!=pattern[j]) j=fail[j-1];
        if(str[i]==pattern[j]){
            if(j==pattern.size()-1){
                result.push_back(i-pattern.size()+1);
                j=fail[j];
            }
            else ++j;
        } 
    }
    return result;
}

std::pair<int, int> kmp(std::string& str, std::string& pattern){
    std::vector<int> fail(std::move(get_fail(pattern)));
    
    for(int i = 0, j = 0; i < str.size(); ++i){
        if(str[i] == pattern[j]){
            int index = i;
            while(j < pattern.size() && str[index] == pattern[j]){
                ++index;
                ++j;
            }
            if(j == pattern.size() && str[index - 1] == pattern[j - 1]) return std::pair<int, int>(i, index - 1);
            else{
                i = fail[j] == 0 ? i + fail[j] : i + fail[j] - 1;
                j = 0;
            }
        }
    }
    return std::pair<int, int>(-1 ,-1);
}

int special_number = 1;
class Trie{
    public:
        Trie() : tree(std::vector<Trie*>(50, nullptr)), is_finished(false), encode_values(std::vector<unsigned int>(50, 0)) {
        }
        ~Trie(){
        }
        unsigned int encode(char ch){
            unsigned char uch = static_cast<unsigned char>(ch);
            unsigned int uint = static_cast<unsigned int>(uch);
            
            if(encode_values.size() - 1 < uint)
                encode_values.resize(encode_values.size() + 100);

            if(encode_values[uint] == 0)
                encode_values[uint] = special_number++;
            
            return encode_values[uint]; 
        }
        void insert(std::string&& str){
            if(str.empty() == true){
                is_finished = true;
                return;
            }
            
            int current = encode(str[0]);
            if(tree.size() - 1 < current) tree.resize(tree.size() + 100);
            if(tree[current] == nullptr) tree[current] = new Trie();
            tree[current]->insert(std::move(std::string(str.begin() + 1, str.end())));
        }
        Trie* find(std::string&& str){
            if(is_finished == true) return this;
            if(str.empty() == true) return nullptr;

            int current = encode(str[0]);
            if(tree[current] == nullptr) return nullptr;
            return tree[current]->find(std::string(str.begin() + 1, str.end())); 
        }
    public:
        std::vector<Trie*> tree;
        bool is_finished;
        std::vector<unsigned int> encode_values;
};

int main(){
    std::string s = "ababababc ababadacad";
    std::string pattern = "ababad";

    BASIC_PRACTICE::print(std::move(get_fail2(pattern)));
    auto result = kmp2(s, pattern);
    for(auto const& i : result)std::cout<<i<<"~"<<i+pattern.size()-1<<"\n";
    // std::cout<<result.first<<" "<<result.second<<"\n";
   

    return 0;
}