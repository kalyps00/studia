import random

def pi(cltwt):
    ltwo = 0
    for _ in range(cltwt):
        x = random.uniform(-1, 1)
        y = random.uniform(-1, 1)
        if x*x + y*y <= 1:
            ltwo += 1

    return 4* ltwo/cltwt
throws = int(input("Enter number of throws: "))
print(pi(throws))
