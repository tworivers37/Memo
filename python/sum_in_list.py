'''
[1, 2, 5, 6, 7, 9, 11] 안에 합이 15가 되는 두 요소의 조합이 있는지 확인하고 싶습니다. 두 요소 6과 9의 합이 15가 되죠? 이 조합이 있는지 없는지를 알고 싶은 거죠.

함수 설명
함수 sum_in_list은 정수 search_sum와 정렬된 정수 리스트 sorted_list를 받아서 sorted_list안의 두 요소의 합이 search_sum가 되는 조합이 있는지 없는지를 불린으로 리턴합니다.

sum_in_list(15, [1, 2, 5, 6, 7, 9, 11])은 불린 True를 리턴합니다
'''


'''
리스트 [1, 2, 3, 9]를 예시로 사용할게요.


각 요소 별로 합이 8이 되는 요소가 있는지 이진 탐색을 이용해서 찾으면 되는데요.


0 번째 요소가 1이니까 나머지 리스트 [2, 3, 9]에 7이 있는지 확인을 하고
1 번째 요소가 2니까 나머지 리스트 [1, 3, 9]에 6이 있는지 확인을 하고
…

이렇게 모든 요소에 합이 7이 되는 다른 인덱스가 있는지 확인하면 되겠죠? 요소의 수가 n일 때, 이진 탐색은 요소를 찾는데 O(lgn)이 걸린다고 배웠는데요. 
총 리스트의 길이인 n번 만큼 이진 탐색을 하니까 O(nlgn)의 시간 복잡도로 문제를 풀 수 있겠네요.

기존의 방식인 O(n^2)보다 더 효율적인 방법을 찾았습니다. 더 효율적인 방법이 있는지 한 번 생각해볼까요?
'''

'''
[1, 2, 6, 7, 9, 11]


1 번째 요소와 5 번째 요소, 2와 11의 합을 15와 비교하면 됩니다. 
애초에 11보다 더 큰 값은 리스트에 없고, 1보다 더 큰 요소는 있기 때문에 0 번째 요소를 1 번째 요소로 바꿔서 확인하는 거죠. 
리스트가 정렬되어 있으니까 1 번째 요소가 적어도 0 번째 요소보다는 크겠죠?

그런데 13도 15보다 작네요.
마찬가지로 더 큰 조합을 찾기 위해서 이번에는 2 번째 요소와 5 번째 요소의 합을 비교하겠습니다. 
6과 11의 합 17은 15보다 크네요.
이번에는 17보다는 작은 합이 있는지 찾아봐야 됩니다.
전과 반대로 5 번째 요소보다 더 작은 요소를 찾아야겠군요. 2 번째 요소와 4 번째 요소의 합을 확인하면 되겠죠?

6과 9의 합은 15네요. 답을 찾았습니다. test_list에는 두 개의 요소의 합이 15가 되는 경우가 있습니다.
'''

'''
[1, 2, 6, 7, 9, 11]

확인할 두 인덱스 변수를 low = 0와 high = len(test_list) - 1라고 정의한다.
반복문을 사용해서 low < high 일 때 동안 아래와 같이 low와 high 변수를 업데이트한다.

low	high	test_list[low] + test_list[high]	Action
00	55	    1 + 11 = 121+11=12	                low 1 증가
11	55	    2 + 11 = 142+11=14	                low 1 증가
22	55	    6 + 11 = 176+11=17	                high 1  감소
22	44	    6 + 9 = 156+9=15	                15를 찾았기 때문에 True 리턴

두 개의 인덱스가 서로 같아지면 더 이상 확인할 필요가 없겠죠?
아무리 왼쪽 인덱스를 늘리고 오른쪽 인덱스를 줄여도 답을 찾을 수 없기 때문입니다. 이때는 False를 리턴해주면 되죠.

이 방법을 사용하면 최악의 경우인 요소 조합이 없을 경우, 
n 개의 요소를 다 확인하겠군요. 이때 시간 복잡도는 O(n)고요.
이진 탐색을 사용했던 방법의 O(nlgn)보다 시간 복잡도가 낫군요
'''

def sum_in_list(search_sum, sorted_list):
    low = 0
    high = len(sorted_list) - 1
    
    while low < high:
        candidate_sum = sorted_list[low] + sorted_list[high]
        
        if candidate_sum == search_sum: # 합이 찾으려는 숫자일 때
            return True
        
        if candidate_sum < search_sum:  # 합이 찾으려는 숫자보다 작을 때
            low += 1
        
        else: # 합이 찾으려는 숫자보다 클 때
            high -= 1
    
    # 찾는 조합이 없기 때문에 False 리턴
    return False