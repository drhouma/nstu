import check_primary
import time

# executes base^(factorial!) % divisor (numbers theory)
def modifiedDivision(base: int, factorial: int, divisor: int) -> int:
    tmp = factorial
    for i in range(1, factorial):
        tmp2 = base ** i
        base = tmp2 % divisor
    return base


# n - факторизуемое число
# k -
def p_m1_PollardFactorization(n: int, k: int) -> int:
    c: int = 1
    for i in range(2, 9):
        if NOD(n, i) == 1:
            c = i
    for i in range(1, k):
        mi = modifiedDivision(c, i, n)
        d = NOD(mi - 1, n)
        if 1 < d < n:
            return d

    return -1


def factorial(n: int) -> int:
    ret: int = 1
    for i in range(1, n):
        ret *= i
    return ret


def NOD(n1: int, n2: int) -> int:
    for i in range(2, n2 // 2 + 1):
        if n1 % i == 0 and n2 % i == 0:
            return i
    return 1


def factorize(number: int, k: int) -> dict:
    if check_primary.LemanTest(number, 10):
        return {}
    mp = p_m1_PollardFactorization(number, k)
    dictionary = dict()
    while mp != -1:
        if mp not in dictionary:
            dictionary[mp] = 1
        else:
            dictionary[mp] = dictionary[mp] + 1
        number = number // mp
        mp = p_m1_PollardFactorization(number, k)

    if number not in dictionary and len(dictionary) != 0:
        dictionary[number] = 1
    elif len(dictionary) != 0:
        dictionary[number] = dictionary[number] + 1
    return dictionary



if __name__ == '__main__':
    # print("Введите число, раскладываемое на множители")
    # number: int = int(input())
    with open("input", "r") as file:
        lines = [line.rstrip() for line in file]
    with open("output", "w") as file:
        for line in lines:
            r = [int(x) for x in line.split()]
            start_time = time.time()
            factors = factorize(r[0], r[1])
            end_time = time.time()
            if len(factors) == 0:
                file.write("Число " + str(r[0]) + " - простое" + '\n')
            else:
                res_str = ""
                summa: int = 0
                for x in factors:
                    summa = summa + factors[x]
                    res_str = res_str + str(x) + '^' + str(factors[x]) + ' '
                res_str = res_str + "Количество итераций: " + str(summa)
                elapsed_miliseconds = str((end_time - start_time) * 1000)
                file.write("Множители числа " + str(r[0]) +": "+ res_str + " Затраченно милисекунд: " + elapsed_miliseconds + '\n')

    # if (not check_primary.LemanTest(number, 10)):
    #     print("smth " + str(p_m1_PollardFactorization(number, 7)))



# See PyCharm help at https://www.jetbrains.com/help/pycharm/
