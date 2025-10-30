import timeit


def pierwsze_imperatywna(n):
    res = []
    for num in range(2, n + 1):
        is_prime = True
        for div in range(2, int(2**0.5) + 1):
            if num % div == 0:
                is_prime = False
                break
        if is_prime:
            res.append(num)
    return res


def pierwsze_skladana(n):
    return [
        num
        for num in range(2, n + 1)
        if all(num % div != 0 for div in range(2, int(2**0.5) + 1))
    ]


def pierwsze_funkcyjna(n):
    def is_prime(num):
        return all(num % div != 0 for div in range(2, int(2**0.5) + 1))

    return list(filter(is_prime, range(2, n + 1)))


if __name__ == "__main__":
    n = 20
    if pierwsze_funkcyjna(n) == pierwsze_skladana(n) == pierwsze_imperatywna(n):
        print("Wszystkie trzy funkcje zwracają ten sam wynik \n")
    print(
        "Imperatywna:",
        f"{timeit.timeit(lambda: pierwsze_imperatywna(n), number=1000):.3f}",
        "s\n",
    )
    print(
        "Skladana:",
        f"{timeit.timeit(lambda: pierwsze_skladana(n), number=1000):.3f}",
        "s\n",
    )
    print(
        "Funkcyjna:",
        f"{timeit.timeit(lambda: pierwsze_funkcyjna(n), number=1000):.3f}",
        "s\n",
    )
