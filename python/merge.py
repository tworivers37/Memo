def merge(list1, list2):
    if not list1 or not list2:
        return list2 if len(list1) == 0 else list1
        
    mid1 = len(list1) // 2
    mid2 = len(list2) // 2
    
    merge(list1[:mid1], list1[mid1 + 1:])
    merge(list2[:mid2], list2[mid2 + 1:])
    
    result_list = []
    i = 0
    j = 0
    
    while i < len(list1) and j < len(list2):
        if list1[i] < list2[j]:
            result_list.append(list1[i])
            i += 1
        else:
            result_list.append(list2[j])
            j += 1
    
    while i < len(list1):
        result_list.append(list1[i])
        i += 1
    while j < len(list2):
        result_list.append(list2[j])
        j += 1
        
    return result_list
    
    
# 테스트
print(merge([1],[]))
print(merge([],[1]))
print(merge([2],[1]))
print(merge([2,2,2],[1,1,1]))
print(merge([1, 2, 3, 4],[5, 6, 7, 8]))
print(merge([5, 6, 7, 8],[1, 2, 3, 4]))
print(merge([4, 7, 8, 9],[1, 3, 6, 10]))


def merge2(list1, list2):
    result_list = []
    i = 0
    j = 0
    
    while i < len(list1) and j < len(list2):
        if list1[i] < list2[j]:
            result_list.append(list1[i])
            i += 1
        else:
            result_list.append(list2[j])
            j += 1
    
    while i < len(list1):
        result_list.append(list1[i])
        i += 1
    while j < len(list2):
        result_list.append(list2[j])
        j += 1
        
    return result_list

# 합병 정렬
def merge_sort(my_list):
    if len(my_list) < 2:
        return my_list
    
    return merge2(merge_sort(my_list[:len(my_list) // 2]), merge_sort(my_list[len(my_list) // 2:]))


# 테스트
print(merge_sort([1, 3, 5, 7, 9, 11, 13, 11]))
print(merge_sort([28, 13, 9, 30, 1, 48, 5, 7, 15]))
print(merge_sort([2, 5, 6, 7, 1, 2, 4, 7, 10, 11, 4, 15, 13, 1, 6, 4]))
