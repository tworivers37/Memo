print("1,2,3,4".split(","))

print("\n\n\t adfasdf asdf asdf123\n\n".strip())

with open("./file", "r") as f:
    for line in f:
        print(line.strip())

with open("./file2", "w") as f:
    for i in range(0,100):
        f.write(f"{i} : test\n")

with open("./file2", "a") as f:
    for i in range(0,100):
        f.write(f"test{i}\n")

# with open("./vocabulary.txt", "w") as file:
#     while True:
#         eng_word = input("영어 단어를 입력하세요:")
#         if eng_word == "q":
#             break
#         file.write(f"{eng_word}: ")
#         kor_word = input("한국어 뜻을 입력하세요:")
#         if kor_word == "q":
#             break
#         file.write(f"{kor_word}\n")

# with open("./vocabulary.txt", "r") as file:
#     for line in file:
#         splited = line.split(":")
#         splited[0].strip()
#         splited[1].strip()

#         value = input(f"{splited[1]}:")
#         if value == splited[0]:
#             print("맞았습니다!")
#         else:
#             print(f"아쉽습니다. 정답은 {splited[0]}입니다.")


import random

dic = {}
values = []

with open("./vocabulary.txt", "r") as file:
    for line in file:
        splited = line.split(":")
        splited[0] = splited[0].strip()
        splited[1] = splited[1].strip()
        dic[splited[0]] = splited[1]

for key in dic.keys():
    values.append(key)

while True:
    index = random.randint(0, len(values) - 1)
    result = input(f"{dic[values[index]]}: ")
    if result == "q":
        break
    if result == values[index]:
        print("맞았습니다!")
    else:
        print(f"틀렸습니다. 정답은 {values[index]}입니다.")

