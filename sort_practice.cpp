#include<iostream>
#include<vector>
#include<random>

void print(std::vector<int> const& values)
{
	std::cout<<"\n********************************************************************************************\n";
	for(auto const& value : values) std::cout<<value<<" ";
	std::cout<<"\n--------------------------------------------------------------------------------------------\n";
}

void set_values(std::vector<int>& values)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 10000);
	for(auto & value : values) value = dist(gen);
}

class heap
{
public:
	heap(int size = 1000)
		: last_index_{0}, values_(size, 0)
	{
	}

	heap(std::vector<int>& values, int begin, int end) 
		: last_index_{0}, values_(end - begin + 1 + 1, 0)
	{
		for(int index = begin; index <= end; ++index)
		{
			insert_node(values[index]);
		}
	}

	void insert_node(int value)
	{
		int index = ++last_index_;
		while(index != 1)
		{
			if(values_[get_parent(index)] > value)
			{
				values_[index] = values_[get_parent(index)];
				index = get_parent(index);
			}
			else break;
		}
		values_[index] = value;
	}

	int delete_node()
	{
		int index = 1;
		int delete_value = values_[index];
		int last_value = values_[last_index_--];

		while(index <= last_index_)
		{
			if(get_priority(index) <= 0) break;
			if(values_[get_priority(index)] < last_value)
			{
				values_[index] = values_[get_priority(index)];
				index = get_priority(index);
			}
			else break;
		}
		values_[index] = last_value;

		return delete_value;
	}

	void print()
	{
		for(auto const& value : values_) std::cout<<value<<" ";
		std::cout<<"\n";
	}
	void print_node()
	{
		for(int i = 0; i < values_.size(); ++i)
			std::cout<<delete_node()<<" ";
		std::cout<<"\n";
	}

private:
	int get_parent(int index){ return index / 2; }
	int get_right(int index){ return index * 2 + 1; }
	int get_left(int index){ return index * 2; }
	int get_priority(int index)
	{
		int left = get_left(index);
		int right = get_right(index);
		if(right <= last_index_) return values_[left] < values_[right] ? left : right;
		else if(left <= last_index_) return left;
		return -1;
	}

	std::vector<int> values_;
	int last_index_;
};

void count_sort(std::vector<int>& values)
{
	int max = values[0];
	for(auto const& value : values) if(max < value) max = value;
	
	std::vector<int> count(max + 1, 0);
	std::vector<int> result(values.size(), 0);
	
	for(auto const& value : values) ++count[value];
	for(int i = 1; i < count.size(); ++i) count[i] += count[i - 1];
	for(int i = values.size() - 1; i >= 0; --i) result[--count[values[i]]] = values[i];
	for(int i = 0; i < values.size(); ++i) values[i] = result[i];
}

void radix_sort(std::vector<int>& values)
{
	int max = values[0];
	for(auto const& value : values) if(max < value) max = value;
	int digit = 0;
	while(max != 0)
	{
		max /= 10;
		++digit;
	}
	for(int i = 0; i < digit; ++i)
	{
		std::vector<int> result(values.size(), 0);
		std::vector<int> count(10, 0);
		int exp = 1;
		for(int j = 0; j < i; ++j) exp *= 10;
		for(auto const& value : values) ++count[(value / exp) % 10];
		for(int j = 1; j < count.size(); ++j) count[j] += count[j - 1];
		for(int j = values.size() - 1; j >= 0; --j) result[--count[(values[j] / exp) % 10]] = values[j];
		for(int j = 0; j < result.size(); ++j) values[j] = result[j];
	}
}

void bubble_sort(std::vector<int>& values)
{
	for(int i = 0; i < values.size(); ++i)
	{
		bool is_sorted = true;
		for(int j = 0; j < values.size() - 1 - i; ++j)
		{
			if(values[j] > values[j + 1])
			{
				std::swap(values[j], values[j + 1]);
				is_sorted = false;
			}
		}
		if(is_sorted == true) break;
	}
}

void select_sort(std::vector<int>& values)
{
	for(int i = 0; i < values.size() - 1; ++i)
	{
		int index = i;
		for(int j = i + 1; j < values.size(); ++j)
		{
			if(values[j] < values[index]) index = j;
		}
		if(index != i) std::swap(values[index], values[i]);
	}
}

void insert_sort(std::vector<int>& values)
{
	for(int i = 1; i < values.size(); ++i)
	{
		int j = i - 1;
		int value = values[i];
		for(; j >= 0; --j)
		{
			if(values[j] > value) values[j + 1] = values[j];
			else break;
		}
		values[j + 1] = value;
	}
}

void insert_sort_util(std::vector<int>& values, int begin, int end)
{
	std::vector<int> copy{values.begin() + begin, values.begin() + end + 1};
	insert_sort(copy);
	std::copy(copy.begin(), copy.end(), values.begin() + begin);
}

void insert_sort_util2(std::vector<int>& values, int begin, int gap)
{
	for(int i = begin + gap; i < values.size(); i += gap)
	{
		int j = i - gap;
		int value = values[i];
		for(; j >= begin; j -= gap)
		{
			if(values[j] > value) values[j + gap] = values[j];
			else break;
		}
		values[j + gap] = value;
	}
}

void shell_sort(std::vector<int>& values)
{
	int gap = (values.size() / 2) % 2 == 0 ? values.size() / 2 + 1 : values.size() / 2;
	while(gap > 0)
	{
		for(int i = 0; i < gap; ++i)
		{
			insert_sort_util2(values, i, gap);
		}

		if(gap == 1) break;

		gap = (gap / 2) % 2 == 0 ? gap / 2 + 1 : gap / 2;
	}
}

void merge(std::vector<int>& values, int begin, int mid, int end)
{
	int first_begin = begin;
	int second_begin = mid + 1;
	int index = begin;
	std::vector<int> tmp(end + 1, 0);

	while(first_begin <= mid && second_begin <= end)
	{
		if(values[first_begin] < values[second_begin]) tmp[index++] = values[first_begin++];
		else tmp[index++] = values[second_begin++];
	}

	while(first_begin > mid && second_begin <= end) tmp[index++] = values[second_begin++];
	while(second_begin > end && first_begin <= mid) tmp[index++] = values[first_begin++];
	for(int i = begin; i <= end; ++i) values[i] = tmp[i];
}

void merge_sort(std::vector<int>& values, int begin, int end)
{
	if(begin < end)
	{
		int mid = (begin + end) / 2;
		merge_sort(values, begin, mid);
		merge_sort(values, mid + 1, end);
		merge(values, begin, mid, end);
	}
}

int pivot1(std::vector<int>& values, int begin, int end)
{
	int pivot = end;
	int start = begin;
	int replace = begin;

	while(start < end)
	{
		if(values[start++] <= values[pivot]) std::swap(values[start - 1], values[replace++]);
	}

	std::swap(values[pivot], values[replace]);

	return replace;
}

int pivot2(std::vector<int>& values, int begin, int end)
{
	int pivot = begin;
	int b = begin + 1;
	int e = end;

	while(b <= e)
	{
		while(values[b] <= values[pivot]) ++b;
		while(values[e] > values[pivot]) --e;
		if(b <= e) std::swap(values[b], values[e]);
	}
	std::swap(values[e], values[pivot]);
	return e;
}

void quick_sort(std::vector<int>& values, int begin, int end)
{
	if(begin <end)
	{
		int pivot = pivot1(values, begin, end);
		//int pivot = pivot2(values, begin, end);

		quick_sort(values, begin, pivot - 1);
		quick_sort(values, pivot + 1, end);
	}
}

void tim_sort(std::vector<int>& values)
{
	const int RUN = 32;
	//insert
	for(int i = 0; i < values.size(); i += RUN)
		insert_sort_util(values, i, i + RUN - 1 < values.size() - 1 ? i + RUN - 1 : values.size() - 1);
	//merge
	for(int i = RUN; i < values.size(); i *= 2)
	{
		for(int j = 0; j < values.size(); j += i * 2)
		{
			int begin = j;
			int end = j + i * 2 - 1 < values.size() - 1 ? j + i * 2 - 1 : values.size() - 1;
			merge_sort(values, begin, end);
		}
	}
}

void intro(std::vector<int>& values, int begin, int end, int depth)
{
	//end - begin < 16
	//insert
	if(end - begin < 16)
	{
		insert_sort_util(values, begin, end);
		return;
	}

	//depth, 2logn
	//heap
	if(depth == 0)
	{
		heap h(values, begin, end);
		for(int i = begin; i <= end; ++i) values[i] = h.delete_node();
		return;
	}

	//quick
	int pivot = pivot1(values, begin, end);
	intro(values, begin, pivot - 1, depth - 1);
	intro(values, pivot + 1, end, depth - 1);
}

void intro_sort(std::vector<int>& values)
{
	int depth = [&]() -> int
	{
		int cnt = 0;
		int size = values.size();
		
		while(size != 0)
		{
			size /= 10;
			++cnt;
		}

		return cnt;
	}();
	
	intro(values, 0, values.size() - 1, depth);
}

int main(){
	std::vector<int> values(5000, 0);
	set_values(values);
	print(values);

	intro_sort(values);
	print(values);

	return 0;
}
