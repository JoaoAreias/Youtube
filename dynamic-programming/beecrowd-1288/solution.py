from sys import stdin


def knapsack(power: list[int], weight: list[int], capacity: int) -> int:
    n = len(power)
    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    for i, wt in enumerate(weight, 1):
        for j in range(1, capacity + 1):
            if wt <= j:
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - wt] + power[i - 1])
            else:
                dp[i][j] = dp[i - 1][j]

    return dp[n][capacity]


def main():
    T = int(stdin.readline())

    for _ in range(T):
        n = int(stdin.readline())
        power, weight = [0] * n, [0] * n

        for i in range(n):
            power[i], weight[i] = map(int, stdin.readline().split())

        k, r = int(stdin.readline()), int(stdin.readline())

        print(
            "Falha na missao"
            if knapsack(power, weight, k) < r
            else "Missao completada com sucesso"
        )


if __name__ == "__main__":
    main()
