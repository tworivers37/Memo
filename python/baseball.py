import random


def generate_numbers():
    numbers = []
    i = 0
    while i < 3:
        random_value = random.randint(0, 9)
        if random_value in numbers:
            continue
        numbers.append(random_value)
        i += 1
    return numbers

def take_guess():
    values = []
    print("숫자 3개를 차례대로 입력하세요.")
    i = 0
    while i < 3:
        value = int(input(f"{i + 1}번쨰 숫자를 입력하세요: "))
        if value in values:
            print("중복되는 숫자입니다. 다시 입력하세요.")
            continue
        elif value < 0 or value > 9:
            print("범위를 벗어나는 숫자입니다. 다시 입력하세요.")
            continue
        else:
            values.append(value)
            i += 1
    
    return values

def get_score(guess, solution):
    strike_count = 0
    ball_count = 0

    for i in range(0, 3):
        if guess[i] == solution[i]:
            strike_count += 1
        elif guess[i] in solution:
            ball_count += 1

    return strike_count, ball_count

ANSWER = generate_numbers()
tries = 0

print("0과 9 사이의 서로 다른 숫자 3개를 랜덤한 순서로 뽑았습니다.")

while True:
    tries += 1
    numbers = take_guess()
    strike, ball = get_score(numbers, ANSWER)
    print(f"{strike}S {ball}B")
    if strike == 3:
        break
print(f"축하합니다. {tries}번 만에 숫자 3개의 값과 위치를 모두 맞추셨습니다.")