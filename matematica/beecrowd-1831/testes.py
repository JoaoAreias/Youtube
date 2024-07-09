from random import randint


def gcd(a, b):
    if a % b == 0:
        return b

    print(f"gcd({a}, {b})")
    return gcd(b, a % b)


print(gcd(314, 159))
