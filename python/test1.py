a = 1
b = 3

print("{0}, {1}".format(a, b))

s = "test {2}"
print(s.format(1,2,3))

print("{0} {1} {2:.4}".format(a, b , a/b))

print("%d" % (a))


name = "name"
age = 32

print("name : %s, age : %d" % (name, age))

print(f"{name}, {age}")
print(f"{a} + {b}")
print(f"{a+b}")


def hello():
    print("helllllll")

print("before")
hello()
print("after")

def square(x):
    return x * x

print(square(100))

def function(a, b, c="test"):
    print(f"{a} aaaaaaaa")
    print(f"{a} + {b}")
    print("{0} + {1}".format(a, b))
    print("{0},{1}".format(a,b))
    print(f"{a + b}")

function(1,2,"cc")

import calculator
print(calculator.add(1,2))
print(calculator.add(11111,2))

import calculator as calc
print(calc.add(88,99))


from calculator import add, sub
print(sub(1,2))


import math
print(math.log(10, 100))
print(math.cos(180))

import random
print(random.random())
print(random.randint(100,200))
print(random.uniform(100,200))

import datetime
day = datetime.datetime(2020, 8, 17)
print(day)
print(type(day))

now = datetime.datetime.now()
print(now)

print(day - now)

add_date = datetime.timedelta(days=10, hours=10)
print(now + add_date)


#a = input("input :")
#print(a)


import random

ROUND = 4
rand_value = random.randint(1, 20)
success = False

print(rand_value)

for i in range(0, ROUND):
    value = int(input(f"기회가 {ROUND - i}번 남았습니다. 1-20 사이의 숫자를 맞춰 보세요: "))
    if value < rand_value:
        print("Up")
    elif value > rand_value:
        print("Down")
    elif value == rand_value:
        print(f"축하합니다. {i + 1}번만에 숫자를 맞추셨습니다.")
        success = True
        break

if success == False:
    print(f"아쉽습니다. 정답은 {rand_value}였습니다.")