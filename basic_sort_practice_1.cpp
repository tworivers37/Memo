#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<cstring>

void print(std::vector<int>& values){
    std::cout<<"-------------------------------------------------------------------------\n";
    for(auto const& value : values) std::cout<<value<<" ";
    std::cout<<"\n-------------------------------------------------------------------------\n";
}

void set_random_values(std::vector<int>& values){
    srand(time(nullptr));
    for(auto & value : values) value = rand() % 100 + 1;
}

class heap{
    public:
        heap(){
            last_index = 0;
            values = std::vector<int>(100, 0);
        }
        heap(std::vector<int>& vals){
            last_index = 0;
            values = std::vector<int>(vals.size(), 0);
            std::for_each(vals.begin(), vals.end(), 
                [&](int val){
                    insert_node(val);
                }
            );
        }
        heap(std::vector<int>& vals, int begin, int end){
            last_index = 0;
            values = std::vector<int>(vals.size(), 0);
            std::for_each(vals.begin() + begin, vals.begin() + end,
                [&](int val){
                   insert_node(val); 
                }
            );
        }
        int get_parent(int current){ return current / 2; }
        int get_right(int current){ return current * 2 + 1;}
        int get_left(int current){ return current * 2;}
        int get_priority(int current){
            int left = get_left(current);
            int right = get_right(current);
            if(right <= last_index) return values[left] < values[right] ? left : right;
            else if(left <= right) return left;
            else return last_index + 1;
        }
        void insert_node(int value){
            int idx = ++last_index;
            while(idx != 0){
                if(values[get_parent(idx)] > value){
                    values[idx] = values[get_parent(idx)];
                    idx = get_parent(idx);
                }
                else break;
            }
            values[idx] = value;
        }
        int delete_node(){
            int idx = 1;
            int delete_value = values[idx];
            int last_value = values[last_index--];
            while(idx <= last_index){
                if(values[get_priority(idx)] < last_value){
                    values[idx] = values[get_priority(idx)];
                    idx = get_priority(idx);
                }
                else break;
            }
            values[idx] = last_value;
            return delete_value;
        }
    private:
        std::vector<int> values;
        int last_index;
};

void count_sort(std::vector<int>& values){
    int max = -1;
    for(auto const& value : values) if(value > max) max = value;
    
    std::vector<int> count(max + 1, 0);
    std::vector<int> result(values.size(), 0);
    for(int i = 0; i < values.size(); ++i) ++count[values[i]];
    for(int i = 1; i < count.size(); ++i) count[i] += count[i-1];
    for(int i = values.size() - 1; i >= 0; --i) result[--count[values[i]]] = values[i];
    for(int i = 0; i < values.size(); ++i) values[i] = result[i];
}

void radix_sort(std::vector<int>& values){
    int max = -1;
    for(auto const& value : values) if(max < value) max = value;

    int digit = 0;
    while(max > 0){
        max /= 10;
        ++digit;
    }

    for(int i = 0; i < digit; ++i){
        int exp = 1;
        std::vector<int> count(10, 0);
        std::vector<int> result(values.size(), 0);

        for(int j = 0; j < i; ++j) exp *= 10;
        for(auto const& value : values) ++count[(value / exp) % 10];
        for(int j = 1; j < count.size(); ++j) count[j] += count[j - 1];
        for(int j = values.size() - 1; j >= 0; --j) result[--count[(values[j] / exp) % 10]] = values[j];
        for(int j = 0; j < values.size(); ++j) values[j] = result[j];
    }
}

void bubble_sort(std::vector<int>& values){
    for(int i = 0; i < values.size(); ++i){
        bool is_sorted = true;
        for(int j = 0; j < values.size() - i - 1; ++j){
            if(values[j] > values[j + 1]){
                std::swap(values[j], values[j + 1]);
                is_sorted = false;
            }
        }
        if(is_sorted == true) break;
    }
}

void select_sort(std::vector<int>& values){
    for(int i = 0; i < values.size() - 1; ++i){
        int tmp = i;
        for(int j = i + 1; j < values.size(); ++j){
            if(values[tmp] > values[j]) tmp = j;
        }
        std::swap(values[i], values[tmp]);
    }
}

void insert_sort(std::vector<int>& values){
    for(int i = 1; i < values.size(); ++i){
        int tmp = values[i];
        int j = i - 1;
        for(; j >= 0; --j){
            if(values[j] > tmp){
                values[j + 1] = values[j];
            }
            else break;
        }
        values[j + 1] = tmp;
    }
}

void merge(std::vector<int>& values, int begin, int mid, int end){
    int b1 = begin;
    int e1 = mid;
    int b2 = mid + 1;
    int e2 = end;
    int index = begin;
    std::vector<int> tmp(end + 1, 0);

    while(b1 <= e1 && b2 <= e2){
        if(values[b1] < values[b2]) tmp[index++] = values[b1++];
        else tmp[index++] = values[b2++];
    }

    while(b1 <= e1 && b2 > e2) tmp[index++] = values[b1++];
    while(b2 <= e2 && b1 > e1) tmp[index++] = values[b2++];
    for(int i = begin; i <= end; ++i) values[i] = tmp[i];
}

void merge_sort(std::vector<int>& values, int begin, int end){
    if(begin < end){
        int mid = (begin + end) / 2;
        merge_sort(values, begin, mid);
        merge_sort(values, mid + 1, end);
        merge(values, begin, mid ,end);
    }
}

int partition(std::vector<int>& values, int begin, int end){
    int pivot = values[end];
    int i = begin;
    for(int j = begin; j < end; ++j){
        if(values[j] < pivot){
            std::swap(values[i++], values[j]);
        }
    }
    std::swap(values[i], values[end]);
    return i;
}

void quick_sort(std::vector<int>& values, int begin, int end){
    if(begin < end){
        int pivot = partition(values, begin, end);
        quick_sort(values, begin, pivot - 1);
        quick_sort(values, pivot + 1, end);
    }
}

void insert_sort_util(std::vector<int>& values, int begin, int end){
    std::vector<int> tmp(values.begin() + begin, values.begin() + end + 1);
    insert_sort(tmp);
    std::copy(tmp.begin(), tmp.end(), values.begin() + begin);
}

void intro_sort_util(std::vector<int>& values, int begin, int end, int depth){
    if(end - begin + 1 < 16){
        insert_sort_util(values, begin, end);
        return;
    }

    if(depth == 0){
        heap h(values, begin, end);
        for(int i = begin; i <= end; ++i) values[i] = h.delete_node();
        return;
    }

    int pivot = partition(values, begin, end);
    intro_sort_util(values, begin, pivot - 1, depth - 1);
    intro_sort_util(values, pivot + 1, end, depth - 1);
}

//intro_sort -> quick + insert + heap
void intro_sort(std::vector<int>& values){
    int depth = [&]() -> int{
        int cnt = 0;
        int size = values.size();
        while(size >= 10){
            size /= 10;
            ++cnt;
        }
        return 2 * cnt;
    }();
    std::cout<<depth<<"\n";
    intro_sort_util(values, 0, values.size() - 1, depth);
}


//tim_sort -> merge + insert, run=32
const unsigned int RUN = 32;
void tim_sort(std::vector<int>& values){
    for(int i = 0; i < values.size(); i += RUN) 
        insert_sort_util(values, i, i + RUN - 1 < values.size() - 1 ? i + RUN - 1 : values.size() - 1);
    for(int i = RUN; i < values.size(); i *= 2){
        for(int j = 0; j < values.size(); j += (i * 2)){
            int begin = j;
            int end = j + (i * 2) - 1 < values.size() - 1 ? j + (i * 2) - 1 : values.size() - 1;
            merge_sort(values, begin, end);
        }
    }
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
    std::vector<int> values(100, 0);
    set_random_values(values);
    print(values);

    intro_sort(values);
    // quick_sort(values,0,values.size()-1);
    print(values);

    Trie* trie = new Trie();
   
    trie->insert(std::move(std::string("testqwert")));
    trie->insert("testqqqqqqqq");
    trie->insert("abcdefg");
    trie->insert("ababababtestaaaa");
    trie->insert("testq");
    
    if(trie->find("test") == nullptr) std::cout<<"nothing\n";
    else std::cout<<"ok\n";

    if(trie->find("testq") == nullptr) std::cout<<"nothing\n";
    else std::cout<<"ok\n";

    return 0;
}