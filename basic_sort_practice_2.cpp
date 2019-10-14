#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>

void print(std::vector<int> const& values){
    std::cout<<"\n--------------------------------------------------\n";
    for(auto const& value : values) std::cout<<value<<" ";
    std::cout<<"\n--------------------------------------------------\n";
}

void set_random(std::vector<int>& values){
    srand(time(nullptr));
    for(auto & value : values) value = (rand() % 100) + 1;
}

class heap{
    public:
        heap(int num){
            last_index = 0;
            values = std::vector<int>(num, 0);
        }
        heap(std::vector<int>& v, int start, int end){
            last_index = 0;
            values = std::vector<int>(v.size(), 0);
            for(int i = start; i <= end; ++i) insert_node(v[i]);
        }

        int get_left(int index){ return index * 2; }
        int get_right(int index){ return index * 2 + 1; }
        int get_parent(int index){ return index / 2 ; }
        int get_priority(int index){
            int left = get_left(index);
            int right = get_right(index);
            if(right <= last_index) return values[left] < values[right] ? left : right;
            else if(left <= last_index) return left;
            else return -1;
        }

        void insert_node(int value){
            int index = ++last_index;
            while(index != 0){
                if(values[get_parent(index)] > value){
                    values[index] = values[get_parent(index)];
                    index = get_parent(index);
                }
                else break;
            }
            values[index] = value;
        }

        int delete_node(){
            int index = 1;
            int delete_value = values[index];
            int last_value = values[last_index--];
            while(index <= last_index){
                int priority = get_priority(index);
                if(priority < 0) break;
                if(values[priority] < last_value){
                    values[index] = values[priority];
                    index = priority;
                }
                else break;
            }
            values[index] = last_value;
            return delete_value;
        }

        void all_delete(){
            int size = values.size();
            std::cout<<"\n";
            for(int i = 0; i < size; ++i) std::cout<<delete_node()<<" ";
            std::cout<<"\n";
        }
    private:
        int last_index;
        std::vector<int> values;
};

void count_sort(std::vector<int>& values){
    int max = -1;
    for(auto const& value : values) if(max < value) max = value;
    
    std::vector<int> result(values.size(), 0);
    std::vector<int> count(max + 1, 0);

    for(auto const& value : values) ++count[value];
    for(int i = 1; i < values.size(); ++i) count[i] += count[i-1];
    for(int i = values.size() - 1; i >= 0; --i) result[--count[values[i]]] = values[i];
    for(int i = 0; i < result.size(); ++i) values[i] = result[i];
}

void radix_sort(std::vector<int>& values){
    int max = -1;
    for(auto const& value : values) if(value > max) max = value;
    int digit = 0;
    while(max != 0){
        ++digit;
        max /= 10;
    }
    for(int i = 0; i < digit; ++i){
        int exp = 1;
        std::vector<int> result(values.size(), 0);
        std::vector<int> count(10, 0);

        for(int j = 0; j < i; ++j) exp *= 10;
        for(int j = 0; j < values.size(); ++j) ++count[(values[j] / exp) % 10];
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
            if(values[j] > tmp){
                values[j + 1] = values[j];
            }
            else break;
        }
        values[j + 1] = tmp;
    }
}

void insert_sort_util(std::vector<int>& values, int begin, int end){
    std::vector<int> tmp(values.begin() + begin, values.begin() + end + 1);
    insert_sort(tmp);
    std::copy(tmp.begin(), tmp.end(), values.begin() + begin);
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
    int pv = end;
    int s = begin - 1;
    for(int i = begin; i < end; ++i){
        if(values[pv] >= values[i]){
            ++s;
            std::swap(values[s], values[i]);
        }
    }
    std::swap(values[pv], values[s + 1]);
    return s + 1;
}

void quick_sort(std::vector<int>& values, int begin, int end){
    if(begin < end){
        int pv = partition(values, begin, end);
        quick_sort(values, begin, pv - 1);
        quick_sort(values, pv + 1, end);
    }
}

//32 insert, merge
const int RUN = 32;
void tim_sort(std::vector<int>& values){
    for(int i = 0; i < values.size(); i += RUN)
        insert_sort_util(values, i, values.size() - 1 < (i + RUN - 1) ? values.size() - 1 : i + RUN - 1);
    for(int i = RUN; i < values.size(); i *= 2){
        for(int j = 0; j < values.size(); j += (i * 2)){
            int right = (j + i * 2 - 1) > values.size() -1 ? values.size() - 1 : (j + i * 2 - 1);
            merge_sort(values, j, right);
        }
    }
}

void intro(std::vector<int>& values, int begin, int end, int depth){
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
    intro(values, begin, pivot - 1, depth - 1);
    intro(values, pivot + 1, end, depth - 1);
}

//end - begin : 16 , insert
//2logn : depth , heap
//quick
void intro_sort(std::vector<int>& values){
    int depth = 2 * log10(values.size());
    intro(values, 0, values.size() - 1, depth);
}


int main(){
    std::vector<int> values(100, 0);
    set_random(values);
    print(values);

    intro_sort(values);
    print(values);

    return 0;
}