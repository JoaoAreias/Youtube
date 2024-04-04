from sys import stdin
from collections import defaultdict


def main():
    t, p = map(int, stdin.readline().split())
    while t != 0 and p != 0:
        # Lista com a penalidade para cata time
        penalties: list[tuple[int, int]] = [(0, 0)] * t
        # Dicionario que agrupa times que resolveram o mesmo número de problemas
        ties: dict[int, list[tuple[int, int]]] = defaultdict(list)

        # -------------------------
        # -     Lendo o Input:    -
        # -------------------------
        for i in range(t):
            line = map(lambda x: x.split("/"), stdin.readline().split())

            a, b, solved = 0, 0, 0
            for tries, time in line:
                if time != "-":
                    solved += 1
                    a += int(tries) - 1
                    b += int(time)

            ties[solved].append((i, a * 20 + b))
            penalties[i] = (a, b)

        # ---------------------------
        # - Resolvelndo o problema: -
        # ---------------------------
        lower_bound, upper_bound = 1, float("inf")

        for tied_teams in ties.values():
            rank = sorted(tied_teams, key=lambda x: x[1])

            for (t1, _), (t2, _) in zip(rank, rank[1:]):
                a1, b1 = penalties[t1]
                a2, b2 = penalties[t2]

                if a1 == a2:
                    continue

                num = b2 - b1
                den = a1 - a2
                ep = num / den

                if ep > 20:
                    upper_bound = min(
                        upper_bound, int(ep) if num % den != 0 else int(ep) - 1
                    )
                elif ep < 20:
                    lower_bound = max(lower_bound, int(ep) + 1)
                else:
                    lower_bound, upper_bound = 20, 20

        upper_bound = upper_bound if upper_bound < float("inf") else "*"
        print(f"{lower_bound} {upper_bound}")

        t, p = map(int, stdin.readline().split())


if __name__ == "__main__":
    main()
