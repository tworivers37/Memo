#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>

void print(std::vector<int>& values){
    for(auto v : values) std::cout<<v<<" ";
    std::cout<<"\n";
}

void values_set(std::vector<int>& values){
    srand(time(nullptr));
    for(auto & v : values) v = rand() % 1000 + 1;
}

class heap{
    public:
        heap()
        : values_(std::vector<int>(100,0)), last_index_(0)
        {}
        heap(std::vector<int>& tmp, int begin, int end)
        : last_index_(0)
        {
            values_ = std::vector<int>(end - begin + 1, 0);
            for(int i=begin; i<=end; ++i) insert_node(tmp[i]);
        }
        int get_parent_index(int current){ return current/2; }
        int get_left_index(int current){ return current*2; }
        int get_right_index(int current){ return current*2+1; }
        int get_priority_index(int current){
            int left = get_left_index(current);
            int right = get_right_index(current);
            if(right<=last_index_) return values_[left] < values_[right] ? left : right;
            else if(left<=last_index_) return left;
            else return last_index_ + 1;
        }
        void insert_node(int value){
            int idx=++last_index_;
            while(idx > 0){
                if(values_[get_parent_index(idx)] > value){
                    values_[idx] = values_[get_parent_index(idx)];
                    idx=get_parent_index(idx);
                }
                else break;
            }
            values_[idx] = value;
        }
        int delete_node(){
            int idx = 1;
            int delete_value = values_[idx];
            int last_value = values_[last_index_--];
            while(idx <= last_index_){
                if(values_[get_priority_index(idx)] < last_value){
                    values_[idx] = values_[get_priority_index(idx)];
                    idx = get_priority_index(idx);
                }
                else break;
            }
            values_[idx] = last_value;
            return delete_value;
        }
        void print(){
            int last = values_.size();
            for(int i = 0; i < last; ++i) std::cout<<delete_node()<<" ";
            std::cout<<"\n";
        }
    private:
        std::vector<int> values_;
        int last_index_;
};

void count_sort(std::vector<int>& values){
    int max = -1;
    for(auto const& v : values) if(v > max) max = v;
    std::vector<int> count(max + 1, 0);
    std::vector<int> result(values.size(), 0);
    for(int i = 0; i < values.size(); ++i) ++count[values[i]];
    for(int i = 1; i < count.size(); ++i) count[i] += count[i-1];
    for(int i = values.size() - 1; i >= 0; --i) result[--count[values[i]]] = values[i];
    for(int i = 0; i < values.size(); ++i) values[i] = result[i];
}

void radix_sort(std::vector<int>& values){
    int max = -1;
    for(auto const& v : values) if(max < v) max = v;
    
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
        for(int j = 0; j < values.size(); ++j) ++count[(values[j] / exp) % 10];
        for(int j = 1; j < count.size(); ++j) count[j] += count[j-1];
        for(int j = values.size() - 1; j >= 0; --j) result[--count[(values[j] / exp) % 10]] = values[j];
        for(int j = 0; j < values.size(); ++j) values[j] = result[j];
    }
}

void bubble_sort(std::vector<int>& values){
    for(int i = 0; i < values.size(); ++i){
        bool is_sorted = true;
        for(int j = 0; j < values.size() - i - 1; ++j){
            if(values[j] > values[j + 1]){
                is_sorted = false;
                std::swap(values[j], values[j + 1]);
            }
        }
        if(is_sorted == true) break;
    }
}

void select_sort(std::vector<int>& values){
    for(int i = 0; i < values.size() - 1; ++i){
        int tmp = i;
        for(int j = i + 1; j < values.size(); ++j){
            if(values[j] < values[tmp]) tmp = j;
        }
        std::swap(values[tmp], values[i]);
    }
}

void insert_sort(std::vector<int>& values){
    for(int i = 1; i < values.size(); ++i){
        int tmp = values[i];
        int j = i - 1;
        for(;j >= 0; --j){
            if(values[j] > tmp) values[j + 1] = values[j];
            else break;
        }
        values[j + 1] = tmp;
    }
}

void merge(std::vector<int>& values, int begin, int mid, int end){
    int s1 = begin;
    int s2 = mid + 1;
    int index = begin;
    std::vector<int> result(end + 1, 0);

    while(s1 <= mid && s2 <= end){
        if(values[s1] < values[s2]) result[index++] = values[s1++];
        else result[index++] = values[s2++];
    }
    while(s1 > mid && s2 <= end) result[index++] = values[s2++];
    while(s2 > end && s1 <= mid) result[index++] = values[s1++];
    for(int i = begin; i <= end; ++i) values[i] = result[i];
}

void merge_sort(std::vector<int>& values, int begin, int end){
    if(begin < end){
        int mid = (begin + end) / 2;
        merge_sort(values, begin, mid);
        merge_sort(values, mid + 1, end);
        merge(values, begin, mid, end);
    }
}

int partition(std::vector<int>& values, int begin, int end){
    int pivot = begin;
    int s = begin + 1;
    int e = end;

    while(s <= e){
        while(values[s] <= values[pivot] && s <= e) ++s;
        while(values[e] > values[pivot] && s <= e) --e;
        if(s <= e) std::swap(values[s], values[e]);
    }
    std::swap(values[e], values[pivot]);
    return e;
}

int partition2(std::vector<int>& values, int begin, int end){
    int pivot = values[end];
    int i = begin - 1;
    for(int j = begin; j < end; ++j){
        if(values[j] <= pivot){
            ++i;
            std::swap(values[i], values[j]);
        }
    }
    std::swap(values[i + 1], values[end]);
    return i + 1;
}

void quick_sort(std::vector<int>& values, int begin, int end){
    if(begin < end){
        int pivot = partition(values, begin, end);
        quick_sort(values, begin, pivot - 1);
        quick_sort(values, pivot + 1, end);
    }
}

void insert_sort_util(std::vector<int>& values, int begin, int end){
    std::vector<int> tmp(end - begin + 1, 0);
    tmp.assign(values.begin() + begin, values.begin() + end + 1);
    insert_sort(tmp);
    std::copy(tmp.begin(), tmp.end(), values.begin() + begin);
}

//tim
//run 32
//insert/merge
const int RUN = 32;
void tim_sort(std::vector<int>& values){
    for(int i = 0; i < values.size(); i += RUN)
        insert_sort_util(values, i, std::min(int(i + RUN -1), int(values.size() - 1)));
    for(int i = RUN; i < values.size(); i *= 2){
        for(int j = 0; j < values.size(); j += (i * 2)){
            int right = std::min(int(j + i * 2 -1), int(values.size() - 1));
            merge_sort(values, j, right);
        }
    }
}


//intro
//insert/heap/quick
//depth 2log(size) //heap
//length < 16 // insert
void intro_sort_util(std::vector<int>& values, int begin, int end, int depth){
    if(end - begin + 1< 16){
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

void intro_sort(std::vector<int>& values){
    int depth = [&]() -> int{
        int size = values.size();
        int log = 0;
        while(size > 1){
            size /= 10;
            ++log;
        }
        return 2 * log;
    }();
    intro_sort_util(values, 0, values.size() - 1, depth);
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
    std::vector<int> values(100,0);
    values_set(values);
    print(values);
    
    return 0;
}