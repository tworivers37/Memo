import random

def generate_numbers(n):
    l = []
    i = 0
    while i < n:
        random_value = random.randint(1, 45)
        if random_value in l:
            continue
        l.append(random_value)
        i += 1

    return l

def draw_winning_numbers():
    return sorted(generate_numbers(6)) + generate_numbers(1)

def count_matching_numbers(list1, list2):
    count = 0
    list1.sort()
    list2.sort()

    for l1 in list1:
        if l1 in list2:
            count += 1
    return count

def check(list1, list2):
    bonus = count_matching_numbers(list1, [list2[-1]])
    count = count_matching_numbers(list1, list2)

    if count == 6 and bonus == 0:
        return 1000000000
    elif count == 6:
        return 50000000
    elif count == 5:
        return 1000000
    elif count == 4:
        return 50000
    elif count == 3:
        return 5000

    return 0


