import sys

MAX = 1000000001

def fill_prefix_sum(country: list[list[int]], t: int) -> list[list[int]]:
    n, m = len(country), len(country[0])
    prefix_sum = [[0 for _ in range(m)] for _ in range(n)]

    prefix_sum[0][0] = int(country[0][0] <= t)

    for i in range(1, n):
        prefix_sum[i][0] = prefix_sum[i-1][0] + int(country[i][0] <= t)

    for j in range(1, m):
        prefix_sum[0][j] = prefix_sum[0][j-1] + int(country[0][j] <= t)

    for i in range(1, n):
        for j in range(1, m):
            prefix_sum[i][j] = int(country[i][j] <= t) + \
                                prefix_sum[i-1][j] + \
                                prefix_sum[i][j-1] - \
                                prefix_sum[i-1][j-1]
    return prefix_sum


def get_sum(prefix_sum: list[list[int]], i: int, j: int, window_size: int) -> int:
    top, left = i - window_size, j - window_size
    sum = prefix_sum[i][j]

    if top >= 0:
        sum -= prefix_sum[top][j]

    if left >= 0:
        sum -= prefix_sum[i][left]

    if top >= 0 and left >= 0:
        sum += prefix_sum[top][left]

    return sum


def is_collapsed(country: list[list[int]], t: int, window_size: int) -> bool:
    n, m = len(country), len(country[0])
    window_size_sq = window_size * window_size
    prefix_sum = fill_prefix_sum(country, t)
    for i in range(window_size - 1, n):
        for j in range(window_size - 1, m):
            if get_sum(prefix_sum, i, j, window_size) == window_size_sq:
                return True
    return False


def main():
    # Lendo os inputs
    n, m, k, _ = map(int, sys.stdin.readline().split())
    country = [[MAX for _ in range(m)] for _ in range(n)]

    for line in sys.stdin:
        a, b, d = map(int, line.split())
        country[a-1][b-1] = d

    # Busca binaria pelo momento em que o pais entrou em colapso
    left, right = 0, MAX
    collapsed = False
    while left < right:
        mid = (right + left) // 2
        if is_collapsed(country, mid, k):
            collapsed = True
            right = mid
        else:
            left = mid + 1

    # Imprime a resposta
    print(right if collapsed else -1)
    

if __name__ == "__main__":
    main()
