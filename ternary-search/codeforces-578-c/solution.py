from sys import stdin
from typing import Iterable

EPS = 1e-6


def poorness(seq: Iterable[float]) -> float:
    first = next(seq)  # type: ignore
    running_sum_pos = first
    running_sum_neg = first
    global_max = abs(first)

    for item in seq:
        running_sum_pos = max(item, item + running_sum_pos)
        running_sum_neg = min(item, item + running_sum_neg)
        global_max = max(global_max, running_sum_pos, abs(running_sum_neg))

    return global_max


def weakness(x: float, seq: list[int]) -> float:
    return poorness(map(lambda v: v - x, seq))


def values_and_error(
    m1: float, m2: float, values: list[int]
) -> tuple[float, float, float]:

    w1 = weakness(m1, values)
    w2 = weakness(m2, values)
    error = abs(w2 - w1)

    return w1, w2, error


def main():
    # Ignora a primeira linha
    _ = stdin.readline()

    values = [int(v) for v in stdin.readline().split()]
    m1, m2 = lb, ub = min(values), max(values)
    w1, w2, error = values_and_error(lb, ub, values)

    # Busca Ternária
    while error > EPS:
        third = (ub - lb) / 3
        m1 = lb + third
        m2 = ub - third

        w1, w2, error = values_and_error(m1, m2, values)

        if w2 > w1:
            ub = m2
        else:
            lb = m1

    x = (m1 + m2) / 2
    print(f"{weakness(x, values):.6f}")


if __name__ == "__main__":
    main()
