'''
(N + 1)의 크기인 리스트에, 1부터 N까지의 임의의 자연수가 요소로 할당되어 있습니다. 그렇다면 어떤 수는 꼭 한 번은 반복되겠지요.

예를 들어 [1, 3, 4, 2, 5, 4]와 같은 리스트 있을 수도 있고, [1, 1, 1, 6, 2, 2, 3]과 같은 리스트가 있을 수도 있습니다. (몇 개의 수가 여러 번 중복되어 있을 수도 있습니다.)

이러한 리스트에서 반복되는 요소를 찾아내려고 합니다.

중복되는 어떠한 수 ‘하나’만 찾아내도 됩니다. 즉 [1, 1, 1, 6, 2, 2, 3]의 예시에서 1, 2를 모두 리턴하지 않고, 1 또는 2 하나만 리턴하게 하면 됩니다.

저번 과제에서는 사전을 정의해서 문제를 푸는 방법을 사용했는데요, 이번 과제에서는 두 가지의 제약이 있습니다.

O(n)O(n) 이상의 공간을 사용할 수 없습니다. 즉 사전이나 리스트와 같이 인풋 리스트의 길이에 비례하는 공간 저장 도구를 사용할 수 없습니다!
인풋으로 받는 리스트 some_list의 요소들을 바꾸거나 변형할 수 없습니다.

'''


'''
number_array = [1, 2, 4, 6, 2, 5, 3] 일 경우를 생각해봅시다.

1 ~ 3 범위에 있는 자연수의 갯수: 4개, 4 ~ 6 범위에 있는 자연수의 갯수: 3개
→ 1 ~ 3 범위에 반복되는 자연수가 있을 수밖에 없다.


1 범위에 있는 자연수의 갯수: 1개, 2 ~ 3 범위에 있는 자연수의 갯수: 3개
→ 2 ~ 3 범위에 반복되는 자연수가 있을 수밖에 없다

2 범위에 있는 자연수의 갯수: 2개 → 반복되는 숫자 2을 찾았다 (끝)
'''

def find_same_number(some_list, start = 1, end = None):
    if end == None:
        end = len(some_list) - 1

    # 반복 요소를 찾으면 리턴한다
    if start == end:
        return start

    # 중간 지점을 구한다
    mid = (start + end) // 2

    # 왼쪽 범위의 숫자를 센다. 오른쪽은 리스트 길이에서 왼쪽 길이를 빼면 되기 때문에 세지 않는다
    left_count = 0

    for element in some_list:
        if start <= element and element <= mid:
            left_count += 1

    # 왼쪽과 오른쪽 범위중 과반 수 이상의 숫자가 있는 범위 내에서 탐색을 다시한다
    if left_count > mid - start + 1:
        return find_same_number(some_list, start, mid)

    return find_same_number(some_list, mid + 1, end)

print(find_same_number([1, 4, 3, 5, 3, 2]))
print(find_same_number([4, 1, 5, 2, 3, 5]))
print(find_same_number([5, 2, 3, 4, 1, 6, 7, 8, 9, 3]))


def find_same_number2(some_list):
    length = len(some_list)
    start = 1
    end = length - 1
    
    while start < end:
        mid_num = (start+end) // 2
        left = 0
        right = 0

        for i in some_list:
            if i <= mid_num:
                left += 1
            elif i > mid_num:
                right += 1
        
        if left > mid_num:
            end = mid_num
        else:
            start = mid_num+1
    
    return start

    