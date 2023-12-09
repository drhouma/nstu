import random
def modifiedPowerDivision(base: int, power: int, divisor: int) -> int:
    divisors = []
    # list indexation start with 0
    counter: int = -1
    # power = n1 * n2 * n3 * ...
    for i in range(2, (power // 2) + 1):
        if (power % i) == 0:
            power = power / i
            divisors.append([i, 1])
            counter += 1
        while (power % i) == 0:
            divisors[counter][1] = divisors[counter][1] + 1
            power = power / i
        if power == 1:
            break
    for x in divisors:
        for i in range(0, x[1]):
            help = base ** x[0]
            base = help % divisor
    return base


# 2^k - вероятность ошибки
def LemanTest(n: int, k: int = 2) -> bool:
    if n <= 0:
        print("incorrect input")
        return False
    if n == 1:
        return True

    res = True
    count_1, count_m1 = 0, 0
    for i in range(0, k - 1):
        # a in [2, n - 1]
        a = random.randint(2, n - 1)
        # t = pow(a, n - 1) % n
        t = modifiedPowerDivision(a, n - 1, n)
        if t == 1:
            count_1 += 1
        elif t == -1:
            count_m1 += 1
        else:
            res = False
            break

    # if count_1 != 0 and count_m1 == 0:
    #     res = False
    return res
